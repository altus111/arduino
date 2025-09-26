#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include "myConnections.h"
#include "EspBoardLed.h"
WebServer server(80);

uint8_t testLed = BUILTIN_LED;

void connect();
void setup(){
  Serial.begin(115200);
  pinMode(testLed,OUTPUT);
  Wifi_Connect();

}

void loop(){
  Serial.print("test");
  digitalWrite(testLed,HIGH);
  delay(500);
  digitalWrite(testLed,LOW);
  delay(500);

}

