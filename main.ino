#include "NeopixelsForUno.hpp"

NeopixelsForUno N(10);
void setup(){
    delay(1);
    N.sendPixel();
}

void loop(){
    delay(50);
    // PORTD = B10000000;
    // delay(1000);
    // PORTD = B00000000;
    // delay(1000);
}