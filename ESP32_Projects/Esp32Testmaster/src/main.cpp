
// ****************************************************************
// Sketch Esp32 Webserver Modular(Tab)
// created: Jens Fleischer, 2018-07-06
// last mod: Jens Fleischer, 2024-05-31
// For more information visit: https://fipsok.de
// ****************************************************************
// Hardware: Esp32
// Software: Esp32 Arduino Core 1.0.0 - 3.1.0
// Getestet auf: ESP32 NodeMCU-32s
/******************************************************************
  Copyright (c) 2018 Jens Fleischer. All rights reserved.

  This file is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This file is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*******************************************************************/
// Der WebServer Tab ist der Haupt Tab mit "setup" und "loop".
// #include <SPIFFS.h> bzw. #include <LittleFS.h> und #include <WebServer.h> 
// müssen im Haupttab aufgerufen werden.
// "server.onNotFound()" darf nicht im Setup des ESP32 Webserver stehen.
// Inklusive Arduino OTA-Updates (Erfordert freien Flash-Speicher)
/**************************************************************************************/
#include <Arduino.h>
#include <WebServer.h>
#include <WiFi.h>
#include "my_preferences.h"

WebServer server(80); //
int ledPin = 33;
void setup(){
  Serial.begin(115200);
  pinMode(ledPin,OUTPUT);
  Wifi_Connect();
  server.begin();
}

void loop()
{
  digitalWrite(ledPin,HIGH);
  delay(500);
  digitalWrite(ledPin,LOW);
  delay(500);
}
