#include <Arduino.h>
#include "myBlinken.h"
//Konstruktor
myBlinken::myBlinken(int pin,int wait)
{   
    Serial.begin(9600);
    Serial.print("Loop1: ");
    Serial.println(pin);
    int _pin = pin;
    //int _pin1 = pin1;
    //int _pin2 = pin2;
    int _wait = wait;
}

// Public Funktionen


void myBlinken::begin()
{

    pinMode(_pin,OUTPUT);
    //pinMode(_pin1,OUTPUT);
    //pinMode(_pin2,OUTPUT);


}
void myBlinken::blink()
{
    
    digitalWrite(_pin,HIGH);
    //digitalWrite(_pin1,HIGH);
    //digitalWrite(_pin2,HIGH);
    delay(_wait);
    digitalWrite(_pin,LOW);
    //digitalWrite(_pin1,LOW);
    //digitalWrite(_pin2,LOW);
    //delay(_wait);

}