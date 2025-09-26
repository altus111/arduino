#include <Arduino.h>
//#include <IRremoteESP8266.h>
//#include <IRsend.h>
#include <IRremote.hpp>
int SenderPin = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
int ledRed = 32;
int ledBlue = 33;
int ledGreen = 12;

void setup() {
 Serial.begin(115200);

 pinMode(SenderPin,OUTPUT);
 IrSender.begin(SenderPin,true,0); 
 pinMode(LED_BUILTIN,OUTPUT);
 pinMode(ledRed,OUTPUT);
 pinMode(ledGreen,OUTPUT);
 pinMode(ledBlue,OUTPUT);
 pinMode(25,INPUT_PULLUP);
 pinMode(26,INPUT_PULLUP);
 pinMode(27,INPUT_PULLUP);
 digitalWrite(ledRed,LOW);
 digitalWrite(ledGreen,LOW);
 digitalWrite(ledBlue,LOW);
}

void loop() {
  
  if (digitalRead(25) == HIGH){
    digitalWrite(ledBlue,LOW);
  } else {
    IrSender.sendNEC(0x0,0x8,1);
    Serial.println("gesendet 0x8");
    digitalWrite(ledBlue,HIGH);
    delay(500);
  } 
  if (digitalRead(26) == HIGH){
    digitalWrite(ledGreen,LOW);
  } else {
    IrSender.sendNEC(0x0,0x5A,1);
    Serial.println("gesendet 0x5A");
    digitalWrite(ledGreen,HIGH);
    delay(500);
  }
  
  if (digitalRead(27) == HIGH){
    digitalWrite(ledRed,LOW);
  }else{
    IrSender.sendNEC(0x0,0x1C,1);
    Serial.println("gesendet 0x1C");
    digitalWrite(ledRed,HIGH);
    delay(500);
  }
   // Serial.println("nix gesendet");
    //delay(100);
 
}

