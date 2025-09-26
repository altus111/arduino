#include <Arduino.h>
#include <Wire.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>

const int ReceiverPin = 5;

void i2cScanner();
int testLed = 17;

void setup() {
 Serial.begin(115200);
 Wire.begin();
 pinMode(testLed,OUTPUT);
 digitalWrite(testLed,HIGH);
 


}

void loop() {
  digitalWrite(testLed,HIGH);
  delay(500);
  digitalWrite(testLed,LOW);
  delay(500);  
 
 
  
}

void i2cScanner(){


}