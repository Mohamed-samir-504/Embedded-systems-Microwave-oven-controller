#include "Popcorn.h"
#include "FSMmanager.h"
#include "lcd_functions.h"
#include "tm4c123gh6pm.h"
#include "Ports_init.h"
#include "delays.h"


void Popcorn_Enter()
{
     CurrentState = Popcorn;
     myStates.Popcorn.Output();	
     myStates.Timer.Enter(1,0);
			
}



void Popcorn_Loop()
{
   
   
}

void Popcorn_Output()
{
     LCD4bits_Cmd(0x01);      //LCD clears
     LCD_WriteString("Popcorn  ");
}

void Popcorn_Init()
{
     myStates.Popcorn.Enter  = Popcorn_Enter;
     myStates.Popcorn.Loop   = Popcorn_Loop;
     myStates.Popcorn.Output = Popcorn_Output;
     loop[Popcorn] = myStates.Popcorn.Loop;

}