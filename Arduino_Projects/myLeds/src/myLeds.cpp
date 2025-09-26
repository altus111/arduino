#include "myLeds.h"
#include <Arduino.h>

myLeds::myLeds(int pina,int pinb,int pinc,int pind)
{     
   _pina = pina;
   _pinb = pinb;
   _pinc = pinc;
   _pind = pind;

    
 }

void myLeds::begin(){

    Serial.print("PinA: ");
    Serial.println(_pina);
    Serial.print("PinB: ");
    Serial.println(_pinb);
    Serial.print("PinC: ");
    Serial.println(_pinc);
    Serial.print("PinD: ");
    Serial.println(_pind);

}

