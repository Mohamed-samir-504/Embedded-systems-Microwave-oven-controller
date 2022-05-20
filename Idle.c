#include "Idle.h"
#include "FSMmanager.h"
#include "keypad.h"
#include "ports_init.h"
#include "lcd_functions.h"
#include "delays.h"

void Idle_Enter()
{
		
	CurrentState = Idle;
	Output_on_leds(0x00);
	myStates.Idle.Output();
		
}


void Idle_Loop()
{
	char x = get_keypad_input();
	if(x == 'A')myStates.Popcorn.Enter();
	else if(x == 'B' || x == 'C')myStates.BeefChicken.Enter(x);
	else if (x == 'D')myStates.FreeTimer.Enter();
	else if(x == 'z')myStates.Locked.Enter(myStates.Locked.PassWord);
	else
	{	
		LCD4bits_Cmd(0x01);
		LCD_WriteString("Err");
		systick_delay_msec(2000);
		myStates.Idle.Enter();
	} 
}


void Idle_Output()
{
		LCD4bits_Cmd(0x01);
		LCD_WriteString("Enter mode");
		systick_delay_msec(500);
}

void Idle_Init()
{
     myStates.Idle.Enter  = Idle_Enter;
     myStates.Idle.Loop   = Idle_Loop;
     myStates.Idle.Output = Idle_Output;
     loop[Idle] = myStates.Idle.Loop;
}
