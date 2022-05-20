//RS and EN are connected to PB0 and PB2 respectively
//data4-7 of lcd are connected to PB4-7
//rows (input) are connected to PE0-3
//columns (output) are connected to PC4-7
//PA2-4 are initialized to be used later with buzzer and push button

#include "tm4c123gh6pm.h"
#include "Ports_init.h"
#include "delays.h"


void PortF_init(void){
	SYSCTL_RCGCGPIO_R |= 0X20;
	while((SYSCTL_PRGPIO_R &= 0X20) == 0);
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R |= 0x1F;
	GPIO_PORTF_AMSEL_R &= ~0x1F;
	GPIO_PORTF_PCTL_R &= ~0x000FFFFF;
	GPIO_PORTF_AFSEL_R &= ~0x1F;
	GPIO_PORTF_DIR_R = 0x0E;
	GPIO_PORTF_DEN_R |= 0x1F;
	GPIO_PORTF_PUR_R |= 0x11;
	GPIO_PORTF_DATA_R &= ~0x0E;	
}




void PortA_init(void){         
	SYSCTL_RCGCGPIO_R |= 0x01;
	while((SYSCTL_PRGPIO_R &= 0x01) == 0);
	GPIO_PORTA_AMSEL_R &= ~0x0C;  
	GPIO_PORTA_PCTL_R &= ~0x0000FF00;
	GPIO_PORTA_AFSEL_R &= ~0x0C;
	GPIO_PORTA_DIR_R |= 0x04;
	GPIO_PORTA_DIR_R &= ~0x08;
	GPIO_PORTA_DEN_R |= 0x0C;
	GPIO_PORTA_PUR_R |= 0x08;
	GPIO_PORTA_DATA_R &= ~0x0C;	
}

void PortB_init(void){        
	SYSCTL_RCGCGPIO_R |= 0x02;
	while((SYSCTL_PRGPIO_R &= 0x02) == 0);
	GPIO_PORTB_AMSEL_R &= ~0xFF;
	GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;
	GPIO_PORTB_AFSEL_R &= ~0xFF;
	GPIO_PORTB_DIR_R |= 0xFF;
	GPIO_PORTB_DEN_R |= 0xFF;
	GPIO_PORTB_DATA_R &= ~0xFF;	
}

void PortC_init(void){        // columns
	SYSCTL_RCGCGPIO_R |= 0x04;
	while((SYSCTL_PRGPIO_R &= 0x04) == 0);
	GPIO_PORTC_AMSEL_R &= ~0xF0;
	GPIO_PORTC_PCTL_R &= ~0xFFFF0000;
	GPIO_PORTC_AFSEL_R &= ~0xF0;
	GPIO_PORTC_DIR_R |= 0xF0;
	GPIO_PORTC_DEN_R |= 0xF0;
	GPIO_PORTC_DATA_R &= ~0xF0;	
	 
	
	
}

void PortE_init(void){       // rows
	SYSCTL_RCGCGPIO_R |= 0x10;
	while((SYSCTL_PRGPIO_R &= 0x010) == 0);
	GPIO_PORTE_AMSEL_R &= ~0x0F;
	GPIO_PORTE_PCTL_R &= ~0x0000FFFF;
	GPIO_PORTE_CR_R |= 0x0F;
	GPIO_PORTE_AFSEL_R &= ~0x0F;
	GPIO_PORTE_DIR_R &= ~0x0F;    
	GPIO_PORTE_DEN_R |= 0x0F;
	GPIO_PORTE_PDR_R |= 0x0F;
	GPIO_PORTE_DATA_R &= ~0x0F;	
}

unsigned char Switch1_input(void){
	return GPIO_PORTF_DATA_R & 0x10;
}

unsigned char Switch2_input(void){
	return GPIO_PORTF_DATA_R & 0x01;
}

unsigned char Switch3_input(void){
  return GPIO_PORTA_DATA_R & 0x08;

}

void Output_on_leds(unsigned char data){
	GPIO_PORTF_DATA_R &= ~0x0E;
	GPIO_PORTF_DATA_R = data;
}

void Buzz_Short(void) {
	
	GPIO_PORTA_DATA_R = 0x04;
	systick_delay_msec(200);
	GPIO_PORTA_DATA_R &= ~0x04;
	
}

void flash(void) {
	int t;
	for(t = 0; t < 3; t++)
	{
		GPIO_PORTA_DATA_R = 0x04;
		Output_on_leds(0x0E);
		systick_delay_msec(500);
		GPIO_PORTA_DATA_R &= ~0x04;
		GPIO_PORTF_DATA_R &= ~0x0E;
		systick_delay_msec(100);
	}
}
	
void blink(void){
		GPIO_PORTF_DATA_R ^= 0x0E;
    systick_delay_msec(500);
    GPIO_PORTF_DATA_R ^= 0x0E;
		systick_delay_msec(100);
}	
	

