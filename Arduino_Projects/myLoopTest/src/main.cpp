#include <Arduino.h>
#include "myBlinken.h"


int LedPin = 8;
//int LedPin1 = 9;
//int LedPin2 = 10;
int wait = 2000;


//myBlinken blinki(LedPin,LedPin1,LedPin2,wait);
myBlinken blinki(LedPin,wait);
void setup() {
  blinki.begin();
  //blinki.blink();
  
  pinMode(LedPin,OUTPUT);
  //pinMode(LedPin1,OUTPUT);
  //pinMode(LedPin2,OUTPUT);
  digitalWrite(LedPin,HIGH);
  //digitalWrite(LedPin1,HIGH);
  //digitalWrite(LedPin2,HIGH);
  
  Serial.begin(9600);
  
}
int i = 0;
void loop() {
  i++;
  Serial.print("Loop: ");
  Serial.println(i);
  blinki.blink();
  // put your main code here, to run repeatedly:
    /*
   digitalWrite(LedPin, HIGH);
  delay(wait);
  digitalWrite(LedPin, LOW);
  delay(wait);
  digitalWrite(LedPin1, HIGH);
  delay(wait);
  digitalWrite(LedPin1, LOW);
  delay(wait);
  digitalWrite(LedPin2, HIGH);
  delay(wait);
  digitalWrite(LedPin2, LOW);
  delay(wait);
  */
 
 
}

