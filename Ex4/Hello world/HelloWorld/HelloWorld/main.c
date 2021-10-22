/*
 * HelloWorld.c
 *
 * Created: 10/22/2021 4:48:10 PM
 * Author : Emoyee
 */ 

#include <avr/io.h>
#include "lcd_8_bit.h"
#define F_CPU = 1000000

int main(void)
{
    /* Replace with your application code */
	char *say_hello = "Hello world"; 
	LCD_Init();
	LCD_DisplayString(say_hello);
    while (1) 
    {		
    }
}

