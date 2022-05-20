#include "BeefChicken.h"
#include "FSMmanager.h"
#include "lcd_functions.h"
#include "delays.h"
#include "keypad.h"
#include "ports_init.h"
#include "tm4c123gh6pm.h"

int y,g,u,h;

void BeefChicken_Enter(int parameter)
{   g=parameter;
    CurrentState = BeefChicken;
		LCD4bits_Cmd(0x01);   //clear LCD
    if(parameter=='B')
		{
			LCD_WriteString("Beef weight?");
			
		}
		else if(parameter=='C')
		{
			LCD_WriteString("Chicken weight?");
		}
		
		y = get_keypad_input()-'0';   //get the weight in kilogram
}


void BeefChicken_Loop()
{   
    if ((y<1 || y>9) && y != 74)            //error case (z-'0' = 74) where z is returned if sw1 is pressed
    {
				LCD4bits_Cmd(0x01);
        LCD_WriteString("Err");
				systick_delay_msec(2000);
        
				myStates.BeefChicken.Enter(g);
				return;
    }
		else if(y == 74) // If pause button is pressed
					{
								myStates.Idle.Enter(); // Enter the Idle State
								return;
	
					}
		else
		{
			LCD4bits_Cmd(0x01); //clear LCD
			LCD_WriteString("Weight is "); 
			LCD4bits_Data(y+'0');
			LCD_WriteString("KGs"); 
			systick_delay_msec(2000);
			LCD4bits_Cmd(0x01);    //clear LCD
			if(g == 'C'){
			
							h = (10* y *1/5);              //Chicken mins
							
							myStates.Timer.Enter((h/10),(h%10)*60/10);
							return;
			}
			else{
						h = (10* y *1/2);			          //Beef mins
						myStates.Timer.Enter((h/10),(h%10)*60/10); 
						return;
			}
		}
    
		
}

void BeefChicken_Output()
{
		
}

void BeefChicken_Init()
{
     myStates.BeefChicken.Enter  = BeefChicken_Enter;
     myStates.BeefChicken.Loop   = BeefChicken_Loop;
     myStates.BeefChicken.Output = BeefChicken_Output;
     loop[BeefChicken] = myStates.BeefChicken.Loop;

}
