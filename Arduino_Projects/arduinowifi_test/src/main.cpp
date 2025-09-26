#include <Arduino.h>
int ledRed = 8;
int ledPin = 7;
void setup() {
    Serial.begin(9600);
    pinMode(ledRed,OUTPUT);
    digitalWrite(ledPin,HIGH);
}

void loop() {
 
}
