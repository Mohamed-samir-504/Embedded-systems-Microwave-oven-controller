#include "Locked.h"
#include "FSMmanager.h"
#include "keypad.h"
#include "ports_init.h"
#include "lcd_functions.h"
#include "delays.h"

int sum,iterator1,iterator2;
char x;
int iterator;
int PasswordFromUser[4];

void Locked_Enter(int* arry)
{		
				LCD4bits_Cmd(0x01);
				systick_delay_msec(500);
        CurrentState = Locked;
        sum = 0;
        iterator = 0;
				myStates.Locked.PassWord = arry;
				for(iterator1 = 0; iterator1<4; iterator1++)PasswordFromUser[iterator1] = 0;
        myStates.Locked.Output();
				systick_delay_msec(700);
}


void Locked_Loop()
{
		
    x = get_keypad_input();
		if(x == 'z')
		{
			myStates.Locked.Enter(myStates.Locked.PassWord);
			return;
		}
		if(iterator <=3)
    {
			LCD4bits_Data('*');
			PasswordFromUser[iterator] = x - '0';
		}
    iterator ++;

    if (iterator > 4 && x == 'x')
    {
        for (iterator2 = 0; iterator2<4; iterator2++) sum += (PasswordFromUser[iterator2] == myStates.Locked.PassWord[iterator2]) ? 1:0;

        if (sum==4)
        {
            LCD4bits_Cmd(0x01);
            LCD_WriteString("Child lock off");
            systick_delay_msec(2000);
            LCD4bits_Cmd(0x01);
            myStates.Idle.Enter();
        }
        else
        {
            LCD4bits_Cmd(0x01);
            LCD_WriteString("WRONG!!!!!!");
            systick_delay_msec(2000);
            LCD4bits_Cmd(0x01);
            myStates.Locked.Enter(myStates.Locked.PassWord);
        }

        return;
    }

}


void Locked_Output()
{
    LCD_WriteString("Child lock on");
    LCD4bits_Cmd(0xC0);
    LCD_WriteString("Password:  ");
}

void Locked_Init()
{
     myStates.Locked.Enter  = Locked_Enter;
     myStates.Locked.Loop   = Locked_Loop;
     myStates.Locked.Output = Locked_Output;
     loop[Locked] = myStates.Locked.Loop;
}