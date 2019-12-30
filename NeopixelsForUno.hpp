#ifndef NEOPIXELSFORUNO_HPP
#define NEOPIXELSFORUNO_HPP
#include "Arduino.h"

class NeopixelsForUno{
protected:
    int pin;
    uint8_t port = 0;
    uint8_t portvalue = 0;
    


public:
    NeopixelsForUno(int pin):
    pin( pin )
    {
        conf();
    }

void clear(){

}

void run(){

}

inline void wait( int32_t n ){
      __asm volatile(                  				
			".rept %[onCycles] \n\t"				
			"nop \n\t"                                              
			".endr \n\t"     
        ::
        [onCycles]	"I" (n)
   ); 
}

void sendBit(bool bit){
    if(bit){
        PORTB = B00000100;
        wait(10);           //wait 58 * 33 = 638 nanoseconds
        PORTB = B00000000;
        //wait 20 * 11 = 220 nanoseconds
}

    else{
        PORTB = B00000100;
        wait(1);        //wait 10 * 11 = 110 nanoseconds
        PORTB = B00000000;
        //wait 58 * 11 = 638 nanoseconds
    }
}

int checkBit(uint8_t value, int number){
    value = value & (1 << number); //to make sure only the chosen index remains
    value = value >> number;       //shift chosen index all the way to the right
    return value;                  //return value is either 0 or 1
}

void sendByte(uint8_t value){
    for(int i = 7; i >= 0; i--){
        int bit = checkBit(value, i);
        sendBit(bit);
    }
}

void sendPixel(){
    for(int i = 0; i < 8; i++){
        sendByte(0);
        sendByte(0);
        sendByte(50);
    } 
    delayMicroseconds(50);
}

void conf(){
    Serial.begin(9600);
    switch(pin){
        case 0 ... 7:
            port = 1;
            portvalue = pin;
            DDRD = DDRD | 1 << portvalue;
            DDRD = DDRD | 0;
            break;
        case 8 ... 13:
            portvalue = pin - 8;
            port = 3;
            DDRB = DDRB | 1 << portvalue;
            DDRB = DDRB | 0;
            break;
        break;
    }
    //mask = mask | (1 << bit);

}

void write_pin(bool bit){
    uint8_t mask = (bit && 1) << portvalue;
    switch(port){
        case 1:
            PORTD = mask;
            return;
        case 3:
            PORTB = mask;
            return; 
    } 

}

void blink(){
    write_pin(1);
    delay(1);
    write_pin(0);
    delay(1);

}

};


#endif 