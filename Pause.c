#include "Pause.h"
#include "FSMmanager.h"
#include "lcd_functions.h"
#include "delays.h"
#include "ports_init.h"
#include "tm4c123gh6pm.h"


void Pause_Enter(int minutes ,int seconds)
{
    myStates.Pause.minutes = minutes;
    myStates.Pause.seconds = seconds;
    CurrentState = Pause;
    LCD4bits_Cmd(0x01);
    myStates.Pause.Output();
}



void Pause_Loop()
{ 
    //LED Blink	
    blink();
	
    if (Switch2_input() == 0)
    {
        myStates.Timer.Enter(myStates.Pause.minutes, myStates.Pause.seconds);
        return;
    }

    if (Switch1_input() == 0) 
    {
        myStates.Idle.Enter();
        return;
    }


}


void Pause_Output()
{
    LCD4bits_Data((myStates.Pause.minutes/10)+'0');// Send second digit in minutes

    LCD4bits_Data((myStates.Pause.minutes%10)+'0'); // Send first digit in minutes

    LCD4bits_Data(':');
    LCD4bits_Data((myStates.Pause.seconds/10)+'0'); // Send second digit in seconds
    LCD4bits_Data((myStates.Pause.seconds%10)+'0'); // Send first digit in seconds
}

void Pause_Init()
{
     myStates.Pause.Enter  = Pause_Enter;
     myStates.Pause.Loop   = Pause_Loop;
     myStates.Pause.Output = Pause_Output;
     loop[Pause] = myStates.Pause.Loop;

}
