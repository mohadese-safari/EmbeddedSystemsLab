/*
 * code.c
 *
 * Created: 10/28/2021 5:15:31 PM
 * Author : Emoyee
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#define  F_CPU = 1000000

int states[] = {8,2,4,1};
int state;
int timer1_initial_value = 65535 - 65000;
void clockWiseRotate();

ISR(TIMER1_OVF_vect){
	TCNT1 = timer1_initial_value;
	
	if(PINC==0){
		clockWiseRotate();
		PORTA = states[state];
	}
	
	
}

int main(void)
{
	DDRA = 0xFF;
	DDRC = 0 ;
	//TCCR0 = (1<<CS00);
	TCCR1B = (1<<CS11);
	TIMSK |= (1 << TOIE1) | (1 << TOIE0); // Enable Timer1 & Timer2 OverFlow Interrupt
	sei();
	
    while (1) 
    {
		/*	
		if(PINC==0){
		clockWiseRotate();
		PORTA = states[state];
		}
		_delay_ms(500);
		*/
		
    }
}

void clockWiseRotate(){
	state = (state+1)% 4;
}

