/*
 * part2.c
 *
 * Created: 10/22/2021 7:13:10 PM
 * Author : Emoyee
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd_8_bit.h"
#define  F_CPU=1000000
int second;
int minute;
int hour;

int timer1_initial_value= 65535-15625;// 31250 ticks for 1 second  15625
void increaseSecond();
void increaseMinute();
void increaseHour();
int secondOverflow();
int minuteOverflow();
int hourOverflow();
void handleClock();
void updateDisplay();
void displayTime();

ISR(TIMER1_OVF_vect){
	handleClock();
	updateDisplay();
	TCNT1 = timer1_initial_value;
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
    	second = 0, minute=0,hour=0;
		LCD_Init();
		updateDisplay();
		
    while (1) 
    {
		
    }
}

void displayTime(){
	LCD_DisplayNumber(hour);
	LCD_DisplayString(":");
	LCD_DisplayNumber(minute);
	LCD_DisplayString(":");
	LCD_DisplayNumber(second);	
}

void updateDisplay(){
	LCD_Clear();
	displayTime();
}

void handleClock(){
	increaseSecond(1);
	
	if(secondOverflow()==1){
		increaseMinute(1);
		second = 0;		
	}
	if(minuteOverflow()){
		minute = minute%60;	
	}
	
	
}

void increaseSecond(int ticks){
	 second= second+ticks;
}

int secondOverflow(){
	if(second>=60){
		return 1;
	}
	return -1;
}

void increaseMinute(int ticks){
	minute= minute+ticks;
}

int minuteOverflow(){
	if(minute>=60){
		minute = minute%60;
		return 1;
	}
	return -1;
}
