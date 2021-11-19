#ifndef keypad_h
#define keypad_h


#define KEY_PORT    PORTB
#define KEY_DDR     DDRB
#define KEY_PIN     PINB

#define C1  PINB4  
#define C2  PINB5 
#define C3  PINB6  
#define C4  PINB7  


/****************functions prototypes*************************************/
void keypad_init(void);
unsigned char key_released(void);
unsigned char key_pressed(void);
unsigned char key_scan(void);

#endif
#include <util/delay.h>
/*****************global variables declaration***************************/
unsigned char table[13] = {
10, 0, 11,
7, 8, 9,
4, 5, 6,
1, 2, 3};

//when you want to read a PIN right after writing to PORT you should wait
unsigned char Delay = 3;
/***********************************************************************/


void keypad_init(void){
    KEY_DDR = 0x0f;
    KEY_PORT = 0xff;
}
/***********************************************************************/
unsigned char key_released(void) {  
    KEY_PORT = 0x70;
    _delay_ms(3);               
    if((KEY_PIN & 0x70) == 0x70)
        return 1;
    else
        return 0;
}
/***********************************************************************/
unsigned char key_pressed(void) {

    KEY_PORT = 0x70;
    _delay_ms(3);
    if( (KEY_PIN & 0x70) != 0x70 ) {
        _delay_ms(20);
        if( (KEY_PIN & 0x70) != 0x70)
        return 1;
    }
    return 0;
}
/***********************************************************************/
unsigned char key_scan(void) {

    unsigned char i, key; 
    if(key_pressed()){ 
        key = 0;
         for(i = 0; i < 4; i++){
            KEY_PORT = ~(1 << i); 
            _delay_ms(3);
            if(!(PINB&(1<<C1)))     key = table[i*3];
            if(!(PINB&(1<<C2)))     key = table[i*3+1];
            if(!(PINB&(1<<C3)))     key = table[i*3+2];
            //if(!C4);       
            }              
         while(!key_released());     
         return key;                
    }    
    else 
        return 255;
}