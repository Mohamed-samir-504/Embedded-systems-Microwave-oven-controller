//Documentation for the LCD Driver V2.0 and its Functions.
//---------------------------------------------------------
// LCD4bits_Data() ----> Prints a Character on the LCD Screen.
// LCD4bits_Cmd()  ----> Excecute a Command on the LCD from the Command Table
// LCD4bits_Init() ----> Initializes the LCD. (Must be executed only once.)
// LCD_Wirite4bits() --> Send 4 bits of the data (This Function is intended to be used internally and SHOULD NOT be used inside the program)
// LCD_WriteString() --> Print a string on the LCD. 
// Cursor_Left(n) -----> Shift cursor to the left by n characters.  
// Cursor_Right(n) ----> Shift cursor to the right by n characters. 

// Note : Data are connected through ports PB4->PB7

#define RS 0x01				 	//RS -> PB0 (0x01)
#define EN 0x04  		 	 	//EN -> PB2 (0x04)
#define Move_Cursor_Left 0x10
#define Move_Cursor_Right 0x14
#define lcd_clear 0x01
#include "tm4c123gh6pm.h"
#include "delays.h"

void LCD_Write4bits(unsigned char data, unsigned char control) //control is RS value , data coming will be in the format of 1234 0000
{
	data &= 0xF0;                       		   	//clear lower 4-bits for control 
	control &= 0x0F;                    				//clear upper 4-bits for data
	GPIO_PORTB_DATA_R = data | control;         //Include RS value (command or data ) with data 
	GPIO_PORTB_DATA_R  = data | control | EN;   //pulse EN
	delay_micro(0);													    //delay for pulsing EN
	GPIO_PORTB_DATA_R  = data | control;				//Turn off the pulse EN
	GPIO_PORTB_DATA_R  = 0;                     //Clear the Data 
}

void LCD4bits_Data(unsigned char data)
{
	LCD_Write4bits(data & 0xF0 , RS);   //send the Upper 4-bits
	LCD_Write4bits(data << 4 , RS);     //then the Lower 4-bits
	delay_micro(40);		    //Delay for LCD 
}


void LCD4bits_Cmd(unsigned char command)
{
	LCD_Write4bits(command & 0xF0 , 0);    //upper 4-bits first
	LCD_Write4bits(command << 4 , 0);      //then lower 4-bits
	
	if(command < 4)
		systick_delay_msec(2);          //commands 1 and 2 need around ~1.64ms (Check LCD Delays Table)
	else
		delay_micro(40);      //other commands take 40 us
}

void LCD4bits_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x02;    //enable clock for PORT B
	systick_delay_msec(10);       //Wait 10 ms to enable the clock of PORTB
  	GPIO_PORTB_DIR_R |= 0xFF;     //Set Port B Pins as Output Pins
	GPIO_PORTB_DEN_R |= 0xFF;     //Enable Port B Digital
	LCD4bits_Cmd(0x28);           //2 lines and 5x7 character (4-bit data, D4 to D7) 
	LCD4bits_Cmd(0x06);           //Automatic Increment cursor (shift cursor to right)
	LCD4bits_Cmd(lcd_clear);      //Clear display screen
	LCD4bits_Cmd(0x0F);           //Cursor Blink
}

void LCD_WriteString(char* str)
{  
	volatile int i = 0;          	//i must be pulled from memory 
	while(*(str+i) != '\0')       	//Continue until you find the Null-Terminating Character.
	{
		LCD4bits_Data(*(str+i)); //Print each character of the string on the LCD
		i++;                        
	}
}

void Cursor_Left(int n)
{
	int CurrentPosition;

	for(CurrentPosition=0; CurrentPosition<n; CurrentPosition++)
	{
		LCD4bits_Cmd(Move_Cursor_Left); // shift left by 1
	}
}

void Cursor_Right(int n)
{
	int CurrentPosition;

	for(CurrentPosition=0; CurrentPosition<n; CurrentPosition++)

	{
		LCD4bits_Cmd(Move_Cursor_Right); // shift right by 1
	}
}


