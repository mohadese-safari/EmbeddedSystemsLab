#include <avr\io.h>
#include <util\delay.h>
 
#define databus_direction DDRC      //  LCD databus Direction Configuration
#define controlbus_direction DDRD  //  LCD Control bus Direction Configuration
 
#define databus	PORTC             //	LCD databus connected to PORTB
#define control_bus PORTD        //	LCD Control bus connected to PORTD
 
#define rs 5                    // Register select pin connected 6th bit(D5) Control bus
#define rw 6                   // Read Write pin connected to 7th bit(D6) Control bus
#define en 7                  // Enable pin connected to 8th bit(D7) Control bus
 
 
/* 16x2 LCD Specification */
#define LCDMaxLines 2
#define LCDMaxChars 16
#define LineOne 0x80
#define LineTwo 0xc0
 
#define BlankSpace ' '

void LCD_Init()
{
    _delay_ms(50);
   databus_direction = 0xff;   // Configure both databus and controlbus as output
   controlbus_direction = 0xff;
   LCD_CmdWrite(0x38);   // LCD 2lines, 5*7 matrix
   LCD_CmdWrite(0x0E);	// Display ON cursor ON
   LCD_CmdWrite(0x01);	// Clear the LCD
   LCD_CmdWrite(0x80);	// Move the Cursor to First line First Position
}

void LCD_Clear()
{
   LCD_CmdWrite(0x01);	// Clear the LCD and go to First line First Position
   LCD_CmdWrite(LineOne);
}

void LCD_GoToLineOne()
{
   LCD_CmdWrite(LineOne);	// Move the Cursor to First line First Position
}

void LCD_GoToLineTwo()
{
   LCD_CmdWrite(LineTwo);	// Move the Cursor to Second line First Position
}

void LCD_GoToXY(char row, char col)
{
   char pos;
 
    if(row<LCDMaxLines)
      {
		 pos= LineOne | (row << 6); // take the line number
		                            //row0->pos=0x80  row1->pos=0xc0
 
	    if(col<LCDMaxChars)
		   pos= pos+col;            //take the char number
		                            //now pos points to the given XY pos
 
		 LCD_CmdWrite(pos);	       // Move the Cursor to specified Position
       }
}

void LCD_CmdWrite( char cmd)
{
 
    databus=cmd;             // Send the command to LCD
    control_bus &=~(1<<rs);  // Select the Command Register by pulling RS LOW
    control_bus &=~(1<<rw);  // Select the Write Operation  by pulling RW LOW
    control_bus |=1<<en;     // Send a High-to-Low Pusle at Enable Pin
   _delay_us(1);
   control_bus &=~(1<<en);
   _delay_ms(1);
}

void LCD_DataWrite( char dat)
{
 
    databus=dat;            // Send the data to LCD
    control_bus |=1<<rs;	// Select the Data Register by pulling RS HIGH
    control_bus &=~(1<<rw);	// Select the Write Operation  by pulling RW LOW
    control_bus |=1<<en;	// Send a High-to-Low Pusle at Enable Pin
	_delay_us(1);
    control_bus &=~(1<<en);
    _delay_ms(1);
 
}

void LCD_DisplayString(char *string_ptr)
{
   while(*string_ptr)
    LCD_DataWrite(*string_ptr++);
 }

void LCD_DisplayNumber(unsigned int num)
{
   LCD_DataWrite((num/10000)+0x30);
   num=num%10000;
 
   LCD_DataWrite((num/1000)+0x30);
   num=num%1000;
 
   LCD_DataWrite((num/100)+0x30);
   num=num%100;
 
   LCD_DataWrite((num/10)+0x30);
 
   LCD_DataWrite((num%10)+0x30);
 
 }

void LCD_ScrollMessage(char *msg_ptr)
{
  unsigned char i,j;
  LCD_CmdWrite(0x0c);			 //Disable the Cursor
  for(i=0;msg_ptr[i];i++)        //Loop to display the complete string
    {                            //each time 16 chars are displayed and
                                 //pointer is incremented to point to next char
 
      LCD_GoToLineOne();                   //Move the Cursor to first line
 
      for(j=0;j<LCDMaxChars && msg_ptr[i+j];j++) //loop to Display first 16 Chars
	    LCD_DataWrite(msg_ptr[i+j]);                 //or till Null char
 
	  for(j=j; j<LCDMaxChars; j++)               //If the chars are below 16
        LCD_DataWrite(BlankSpace);              //then display blank spaces
 
       _delay_ms(500);
    }
   LCD_CmdWrite(0x0E);			  //Enable the Cursor
}