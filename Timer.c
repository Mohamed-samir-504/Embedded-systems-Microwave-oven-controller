#include "Timer.h"
#include "FSMmanager.h"
#include "lcd_functions.h"
#include "tm4c123gh6pm.h"
#include "delays.h"
#include "ports_init.h"

int flag = 0;


void Timer_Enter(int minutes ,int seconds) // Enter Timer State
{

    myStates.Timer.minutes = minutes; // Current Number of Minutes = minutes
    myStates.Timer.seconds = seconds; // Current Number of Seconds = seconds
    CurrentState = Timer; // Set the current state to be the timer
    myStates.Timer.Output(); // show the current time (first second)
    while(Switch2_input() != 0)// Wait until you press the start button
			{
			if(Switch1_input()==0) // If pause button is pressed
					{
								myStates.Idle.Enter(); // Enter the Idle State
								return;
	
					}
			} 
    LCD4bits_Cmd(0x01); // Clear the Screen
    while(Switch3_input() == 0) // If door is opened
    {
				LCD_WriteString("Door is open!"); //Print a message on the screen
				systick_delay_msec(1000); // wait 1 second
				LCD4bits_Cmd(0x01); // clear screen
    }
		Output_on_leds(0x0E); // Turn on LED's
}


void Timer_Loop() // Enter Timer Loop (a loop that stays infinitely until Timer is over or you enter pause state)
{

     Timer_Output(); //Print the Current time on Screen.
	
     if(myStates.Timer.seconds == 0 && myStates.Timer.minutes == 0) 
      {
					LCD4bits_Cmd(0x01); //Clear Screen 
					LCD_WriteString("Finished"); // Print "Finished"
					flash();
					systick_delay_msec(3000); // Wait 3 Seconds
					myStates.Idle.Enter(); // Enter the Idle State
					return;
      }
	
			flag = Systick_RF(1000); // Wait for 1 Second and Check the Flags while waiting.
				
			myStates.Timer.seconds--;

			if(myStates.Timer.seconds == -1) // in the end of a minute
			{
					myStates.Timer.minutes--;
						
					myStates.Timer.seconds = 59; //set the seconds to 59
			}

			if(flag == 1 || flag == 3) // if pause is pressed or the door is open.
			{
					myStates.Pause.Enter(myStates.Timer.minutes, myStates.Timer.seconds); // Enter Paused State
					return;


			}
			LCD4bits_Cmd(0x01); //Clear Screen


}


void Timer_Output()
{
    LCD4bits_Data((myStates.Timer.minutes/10)+'0');// Send second digit in minutes
    LCD4bits_Data((myStates.Timer.minutes%10)+'0'); // Send first digit in minutes
    LCD4bits_Data(':');
    LCD4bits_Data((myStates.Timer.seconds/10)+'0'); // Send second digit in seconds
    LCD4bits_Data((myStates.Timer.seconds%10)+'0'); // Send first digit in seconds
	
}



void Timer_Init()
{
     myStates.Timer.Enter  = Timer_Enter;
     myStates.Timer.Loop   = Timer_Loop;
     myStates.Timer.Output = Timer_Output;
     loop[Timer] = myStates.Timer.Loop;

}