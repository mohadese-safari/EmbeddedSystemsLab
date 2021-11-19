/*
* part2.c
*
* Created: 10/22/2021 7:13:10 PM
* Author : Emoyee
*/

//
#include <avr/io.h>
#include <avr/interrupt.h>

#include "lcd_8_bit.h"
#include "keypad.h"
#include "util\delay.h"
#define  F_CPU = 1000000

//int timer1_initial_value= 65535-15625;// 31250 ticks for 1 second  15625
//int timer1_initial_value= 65535-12650;// 31250 ticks for 1 second  15625

void updateDisplay();
const int MAX_ALLOWED_LENGTH = 10;

ISR(TIMER1_OVF_vect){
	updateDisplay();
	//TCNT1 = timer1_initial_value;
}

//int main(void)
//{
//DDRD = 0xFF;
//DDRC=0xFF;
//PORTC=0x00;
//TCCR1B = ((1<<CS11) | (1<<CS10));
//TIMSK |= (1 << TOIE1); // Enable Timer0 OverFlow Interrupt
//sei();
//TCNT1 = timer1_initial_value;
//second = 0, minute=0,hour=0;
//LCD_Init();
//updateDisplay();
//
//while (1)
//{
//
//}
//}


void main(void)
{
	// Declare your local variables here
	unsigned char str[10],i;
	DDRD = 0xFF;
	DDRC=0xFF;
	PORTC=0x00;
	
	LCD_Init(16);
	LCD_GoToXY(0,0);

	keypad_init();
	while (1)
	{
		i = key_scan();
		if(i != 255){
			LCD_Clear();
			
			if(strlen(str)<MAX_ALLOWED_LENGTH)
			sprintf(str,"%s%d",str,i);
			
			LCD_DisplayString(str);
		}
	}

}

void updateDisplay(){
	LCD_Clear();
}
