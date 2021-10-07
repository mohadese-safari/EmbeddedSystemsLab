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
	DDRA = 1;
    /* Replace with your application code */
    while (1) 
    {
		PORTA = 0x01;
		_delay_ms(500);
		PORTA = 0x00;
		_delay_ms(500);
    }
}

