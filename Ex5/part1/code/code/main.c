/*
 * code.c
 *
 * Created: 10/28/2021 5:15:31 PM
 * Author : Emoyee
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define  F_CPU = 1000000

void clockWiseRotate();
int states[] = {8,2,4,1};
int state;

int main(void)
{
	DDRA = 0xFF;
	DDRC = 0 ;
	
    while (1) 
    {
		if(PINC==0){
		clockWiseRotate();
		PORTA = states[state];
		}
		_delay_ms(500);
    }
}

void clockWiseRotate(){
	state = (state+1)% 4;
}

