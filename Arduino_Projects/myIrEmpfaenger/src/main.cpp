#include <Arduino.h>
#include <IRremote.hpp>


//int ReceiverPin = 5;
//int ledRedPin = 4;
//int ledBluePin = 2;

int ledPins[] = {5,4,2};

void setup() {
  Serial.begin(115200);
  //pinMode(LED_BUILTIN,OUTPUT);
  for (int i=1;i<= 2;i++){pinMode(ledPins[i],OUTPUT);}
  for (int i=1;i <= 2;i++){digitalWrite(ledPins[i],HIGH);}
  IrReceiver.begin(ledPins[0],DISABLE_LED_FEEDBACK);
  printActiveIRProtocols(&Serial);
  

}

void loop() {
  
  //digitalWrite(LED_BUILTIN,HIGH);
  //digitalWrite(ledPin,HIGH);
  //delay(500);
  //digitalWrite(LED_BUILTIN,LOW);
  //digitalWrite(ledPin,LOW);
  
    //Serial.print("Empfange: ");
    //Serial.println(IrReceiver.decodedIRData.command);
    //delay(100);
    if (IrReceiver.decodedIRData.command == 0x8){
      if (digitalRead(ledPins[1]) == 0){
        digitalWrite(ledPins[1],HIGH);

      }
      
    }
    if (IrReceiver.decodedIRData.command == 0x5A){
      if (digitalRead(ledPins[2]) == 0){
        digitalWrite(ledPins[2],HIGH);
      }
    }
    if (IrReceiver.decodedIRData.command == 0x1C){ // wenn ok gedrueckt wird
        digitalWrite(ledPins[1],LOW);digitalWrite(ledPins[2],LOW);      
    } 
 
  if (IrReceiver.decode()){
    IrReceiver.printIRResultShort(&Serial);
    Serial.println();
    IrReceiver.resume();
  }
  

}
