#include "tm4c123gh6pm.h"
#include "ports_init.h"


//extra delay functions

void delay_micro(int n){
      int i,j;
      for(i=0;i<n;i++)
      for(j=0;j<3;j++)
			{}

}

//systick delay functions
void SysTick_Wait(unsigned long delay) // delay = number of ticks
{
      NVIC_ST_CTRL_R = 0X00;
      NVIC_ST_RELOAD_R = delay - 1;
      NVIC_ST_CURRENT_R = 0;
      NVIC_ST_CTRL_R = 0X05; // ENABLE TIMER AND CLK SRC
      while((NVIC_ST_CTRL_R&0x00010000)==0) 
      {
      //wait for count flag
      }
}

void SysTick_Wait1ms()
{
      SysTick_Wait(16000);
}
void systick_delay_msec(int t) //delay by milli seconds.
{
      int i; 
      for(i=0; i<t; i++)
            {
            SysTick_Wait1ms();
            }
}

int Systick_RF(int t) // Systick Wait 1ms and Return Flag
{
	int i;
	int flag = 0;
	for(i = 0; i<t; i++)
	{

		SysTick_Wait1ms();

		if((GPIO_PORTF_DATA_R&0x10) == 0) // PF0 (Pause) is pressed
		{
			flag = 1;
		}

		if((GPIO_PORTF_DATA_R&0x01) == 0) // PF1 (Start is pressed)
		{
			flag = 2;
		}
		if(Switch3_input() == 0) // PA3 (Doon is open) 
		{
			flag = 3;
		}	

	}
	return flag;
}

//Flag Modes:
// 0 --> Nothing is Pressed
// 1 --> Pause Button Was Pressed
// 2 --> Stop Button Was Pressed



