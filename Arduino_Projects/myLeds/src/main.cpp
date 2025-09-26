#include "avr8-stub.h"
#include "app_api.h"
#include <Arduino.h>
#include "myLeds.h"
int tDelay = 100;
int latchPin = 6;      // (6) ST_CP [RCK] on 74HC595
int clockPin = 3;      // (3) SH_CP [SCK] on 74HC595
int dataPin = 12;     // (12) DS [S1] on 74HC595

byte leds = 0;

//int tmp[] = {9,10,11,4};
myLeds myLedis(9,10,11,4);
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}

void setup() {
  Serial.begin(9600);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  digitalWrite(latchPin, HIGH);
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
}

void loop() {
  myLedis.begin();
  leds = 0;
  updateShiftRegister();
  delay(tDelay);
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(tDelay);
  }
}
