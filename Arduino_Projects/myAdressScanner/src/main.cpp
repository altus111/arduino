#include <Arduino.h>
//#include <Morse.h>

int LedPin = 9;
int Led_Pin = 8; 

//Morse morse(LedPin);
void setup() {
//morse.begin();
pinMode(Led_Pin,OUTPUT);
pinMode(LedPin,OUTPUT);
digitalWrite(Led_Pin,HIGH);
digitalWrite(Led_Pin,HIGH);
delay(1000);
digitalWrite(Led_Pin,LOW);
digitalWrite(Led_Pin,LOW);

}
int i = 0;
void loop() {
    Serial.print("Loop: ");
    Serial.println(i);
  //for(int i=0;i<100;i++){
  i++;
    Serial.print("Loop: ");
    Serial.println(i);
    digitalWrite(Led_Pin,HIGH);
    digitalWrite(LedPin,HIGH);
    delay(500);
    digitalWrite(Led_Pin,LOW);
    digitalWrite(LedPin,LOW);
  //}
  

 /* 
  morse.dot(); morse.dot(); morse.dot();
  //digitalWrite(Led_Pin,LOW);
  morse.dash(); morse.dash(); morse.dash();
  //digitalWrite(Led_Pin,HIGH);
  //delay(500);
  morse.dot(); morse.dot(); morse.dot();
  digitalWrite(Led_Pin,LOW);
  delay(1000);
  digitalWrite(Led_Pin,HIGH);
  */
}
