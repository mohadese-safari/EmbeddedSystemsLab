/*
 * src.c
 *
 * Created: 10/7/2021 1:14:02 PM
 * Author : Emoyee
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRA = 0;
	DDRB = 255;
    /* Replace with your application code */
    while (1) 
    {
		if(PINA==0x01){
			PORTB = 255;
			_delay_ms(500);
			PORTB = 0;
			_delay_ms(500);
		}
    }
}

