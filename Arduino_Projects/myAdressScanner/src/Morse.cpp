#include <Arduino.h>
#include <Morse.h>


Morse::Morse(int pin)
{
    int _pin = pin;
 
}
void Morse::begin()
{
  pinMode(_pin, OUTPUT);
}

void Morse::dash()
{
  digitalWrite(_pin, HIGH);
  delay(2000);
  digitalWrite(_pin, LOW);
  delay(250);
}
void Morse::dot()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);  
}