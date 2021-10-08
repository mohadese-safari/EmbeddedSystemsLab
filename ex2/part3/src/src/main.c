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
	unsigned char c = 1 ;
    float factor = 2 ;
	
    /* Replace with your application code */
    while (1) 
    {
		
		PORTB = 0;
		if(PINA==0x01){
			PORTB = c;
			_delay_ms(500);
			c = c * factor;
			if(PORTB==2)
			factor = 2;
			if (PORTB==64)
			factor = .5;
		}
    }
}

