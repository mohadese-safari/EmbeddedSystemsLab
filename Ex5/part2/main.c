/*
 * code.c
 *
 * Created: 10/28/2021 5:15:31 PM
 * Author : Emoyee
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int states[] = {8,2,4,1};
int state;
int direction;
int timer1_initial_value = 65535 - 65000;
void rotate();

ISR(TIMER1_OVF_vect){
	TCNT1 = timer1_initial_value;	
		rotate();
		PORTA = states[state];
}

ISR(INT0_vect){
	direction *=-1;
}

int main(void)
{
	direction = 1;
	DDRA = 0xFF;
	DDRC = 0 ;
	//TCCR0 = (1<<CS00);
	TCCR1B = (1<<CS11);
	TIMSK |= (1 << TOIE1) | (1 << TOIE0); // Enable Timer1 & Timer2 OverFlow Interrupt
	GICR |= (1 << INT0);
	MCUCR |= (1 << ISC01);
	sei();
	
    while (1) 
    {		
    }
}

void rotate(){
	state = (state+direction+4)% 4;
}

