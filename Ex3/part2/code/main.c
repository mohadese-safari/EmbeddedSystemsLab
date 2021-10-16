/*
 * counter.c
 *
 * Created: 10/15/2021 5:15:36 PM
 * Author : Emoyee
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU = 1000000UL
int digits[]={0b10111111,0b10000110,0b11011011,0b11001111,0b11100110,0b11101101,0b11111101,0b10000111,0b11111111,0b11101111}; 
int segments[] = {0b11111110,0b11111101,0b11111011,0b11110111};
int count;
int lcd_index = 0;
int timer0_initial_value = 255-255; // 125 = ticks for 1 millisecond
int timer1_initial_value= 65535-15625;// 31250 ticks for 1 second  15625
void showSegment(int);

ISR(TIMER0_OVF_vect){
	TCNT0 = timer0_initial_value;
	showSegment(lcd_index);
	lcd_index= (lcd_index+1)%4 ;
}

ISR(TIMER1_OVF_vect){
	TCNT1 = timer1_initial_value;
	count= (count+1)%10000;
}

int main(void)
{
    DDRD = 0xFF;
	DDRC=0xFF;
	PORTC=255;
	TCCR0 = (1<<CS00);
	TCCR1B = ((1<<CS11) | (1<<CS10));
	TIMSK |= (1 << TOIE1) | (1 << TOIE0); // Enable Timer1 & Timer2 OverFlow Interrupt
	sei();
	count = 0;
    while (1) 
    {
    }
}

void showSegment(int lcd_index){
	int index;
	if (lcd_index == 3){
		index = count%10;
		PORTD = digits[index];
		PORTC=segments[3];
	}else if (lcd_index == 2){
		index = (count/10)%10;
		PORTD = digits[index];
		PORTC=segments[2];
	}else if (lcd_index==1){
		index = (count/100)%10;
		PORTD = digits[index];
		PORTC=segments[1];
	}else{
		index = (count/1000)%10;
		PORTD = digits[index];
		PORTC=segments[0];
	}	
}
