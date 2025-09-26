#include <Arduino.h>

int testLed = BUILTIN_LED;

void setup() {
  Serial.begin(115200);
  pinMode(testLed,OUTPUT);
  digitalWrite(testLed,OUTPUT);
}

int i =0;
void loop() {
    Serial.print("Zähler ");Serial.println(i);
    digitalWrite(testLed,HIGH);
    delay(500);
    digitalWrite(testLed,LOW);
    delay(500);

  i++;
}
