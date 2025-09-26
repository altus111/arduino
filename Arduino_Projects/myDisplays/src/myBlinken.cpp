#include <Arduino.h>
#include <myBlinken.h>


myBlinken::myBlinken(int pin,int wait)
{
    digitalWrite(pin,HIGH);
    delay(wait);
    pinMode(pin,OUTPUT);
    digitalWrite(pin,LOW);

}




