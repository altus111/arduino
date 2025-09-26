#include <Arduino.h>
int LedPin = 10;
void setup()
{

  pinMode(LedPin, OUTPUT);
}

void loop()
{   
    digitalWrite(LedPin, HIGH);
    delay(100);
    digitalWrite(LedPin, LOW);
    delay(500);
}

