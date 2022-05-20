#include <stdio.h>
#include "FSMmanager.h"
#include "keypad.h"
#include "ports_init.h"
#include "lcd_functions.h"

int main()
{	
		
		int password[4] = {4,6,9,0};
		LCD4bits_Init();
		PortF_init();
		PortC_init();
		PortE_init();
		PortA_init();
		LCD4bits_Cmd(0x0C); //display on , cursor off
		
     
		FSM_int();
		CurrentState = Locked;
		

    myStates.Locked.Enter(password);
     
    while (1) loop[CurrentState]();


}
