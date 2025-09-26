#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
int LedPin = 8;
int redPin = 11;   // R petal on RGB LED module connected to digital pin 11 
int greenPin = 10; // G petal on RGB LED module connected to digital pin 9 
int bluePin = 9;   // B petal on RGB LED module connected to digital pin 10 
#define NODE_ADDRESS 2
#define PAYLOAD_SIZE 2
byte nodePayload[PAYLOAD_SIZE];
void color(char farbe){ // Farbdefinitionen fuer RGB-LED.Erweiterbar
    switch (farbe)
    {
    case 'r':
      digitalWrite(redPin, 255);
      digitalWrite(greenPin, 0);
      digitalWrite(bluePin, 0);
      break;
    case 'g':
      digitalWrite(redPin, 0);
      digitalWrite(greenPin, 255);
      digitalWrite(bluePin, 0);
      break;
    case 'b':
      digitalWrite(redPin, 0);
      digitalWrite(greenPin, 0);
      digitalWrite(bluePin, 255);
      break;
    case 'y':
      digitalWrite(redPin, 255);
      digitalWrite(greenPin, 255);
      digitalWrite(bluePin, 0);
      break;
    case 'w':
      digitalWrite(redPin, 255);
      digitalWrite(greenPin, 255);
      digitalWrite(bluePin, 255);
      break;
    case 'p':
      digitalWrite(redPin, 128);
      digitalWrite(greenPin, 0);
      digitalWrite(bluePin, 255);
      break;  
    default:
      break;
    }

}

void receiveEvent(int howMany){

  while(Wire.available())
    
  {
    char c = Wire.read();
    if(c == 'H')
    {
    color('b');
    delay(1000);
      digitalWrite(LedPin,HIGH);
    }
    else if(c == 'L')
    {
      color('b');
      digitalWrite(LedPin,LOW);
    }
    else{
      color('red');
    
    }
  }
}
void requestEvent()
{
  nodePayload[0] = NODE_ADDRESS;
  nodePayload[1] = analogRead(A0) / 4;
  Wire.write(nodePayload, PAYLOAD_SIZE);
}

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Wire.begin(50);
  pinMode(LedPin,OUTPUT);
  digitalWrite(LedPin,HIGH);
  pinMode(redPin, OUTPUT);   // sets the redPin to be an output 
  pinMode(greenPin, OUTPUT); // sets the greenPin to be an output 
  pinMode(bluePin, OUTPUT);  // sets the bluePin to be an output  
  color('p');
  Wire.onReceive(receiveEvent); // erstelle ein Empfangen-Ereignis
  Wire.onRequest(requestEvent); // erstelle ein Anfrage-Ereignis
}
void loop() {
}
