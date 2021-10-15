#include <avr/io.h>
#include <avr/interrupt.h>
int digits[]={0b10111111,0b10000110,0b11011011,0b11001111,0b11100110,0b11101101,0b11111101,0b10000111,0b11111111,0b11101111};
int count;
int timer1_initial_value= 65535-15625;// 31250 ticks for 1 second  15625
void showSegment();


ISR(TIMER1_OVF_vect){
	showSegment();
	TCNT1 = timer1_initial_value;
	count= (count+1)%10;
}

int main(void)
{
	DDRD = 0xFF;
	DDRC=0xFF;
	PORTC=0x00;
	TCCR1B = ((1<<CS11) | (1<<CS10));
	TIMSK |= (1 << TOIE1); // Enable Timer0 OverFlow Interrupt
	sei();
	TCNT1 = timer1_initial_value;
	count = 0;
	while (1)
	{
	}
}

void showSegment(){
	int index = count%10;
	PORTD = digits[index];
}

