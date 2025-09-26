
// ****************************************************************
// Sketch Esp32 Webserver Modular(Tab)
// created: Jens Fleischer, 2018-07-06
// last mod: Jens Fleischer, 2024-05-31
// For more information visit: https://fipsok.de
// ****************************************************************
// Hardware: Esp32
// Software: Esp32 Arduino Core 1.0.0 - 3.0.0
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
#include <WebServer.h>
//#include <ESP32WebServer.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
  
#ifdef USE_LittleFS
  #define SPIFFS LittleFS
  #include <LittleFS.h>
#else
  #include <SPIFFS.h>
#endif

#define DEBUGGING                     // Einkommentieren für die Serielle Ausgabe

#ifdef DEBUGGING
#define DEBUG_B(...) Serial.begin(__VA_ARGS__)
#define DEBUG_P(...) Serial.println(__VA_ARGS__)
#define DEBUG_F(...) Serial.printf(__VA_ARGS__)
#else
#define DEBUG_B(...)
#define DEBUG_P(...)
#define DEBUG_F(...)
#endif
const char* ssid = "UPC0128016";             // Network name.
const char* password = "c9zxScwDnndq";            // Password network.
int ledPin4 = 4;
int ledPin5 = 5;
WebServer server(80);
void Connect() {                                 // Funktionsaufruf "Connect();" muss im Setup nach "spiffs();" eingebunden werden
  pinMode(LED_BUILTIN, OUTPUT);                  // OnBoardLed ESP32 Dev Module
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, 1);
    delay(250);
    digitalWrite(LED_BUILTIN, 0);
    delay(250);
    DEBUG_F(".");
    if (millis() > 10000) {
      DEBUG_P("\nVerbindung zum AP fehlgeschlagen\n\n");
      ESP.restart();
    }
  }
  DEBUG_P("\nVerbunden mit: " + WiFi.SSID());
  DEBUG_P("Esp32 IP: " + WiFi.localIP().toString() + "\n");
}



void esp32Led() {                  //Html Seite
  if (server.hasArg("led")) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));        // LED umschalten
    DEBUG_P(digitalRead(LED_BUILTIN) ? "LED ist aus" : "LED ist an");
  }
  char temp[760];
  snprintf(temp, sizeof temp, R"(<!DOCTYPE html>
<html lang="de">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body {
        background-color: #a9a9a9;
        display: flex;
        flex-flow: column;
        align-items: center;
      }
      input {
        height: 2.5em;
        width: 8em;
        font-size: 1em;
      }
      [value$=n] {
        background-color: #adff2f;
      }
      [value$=s] {
        background-color: red;
      }
    </style>
    <title>Onboard Led</title>
  </head>
  <body>
    <h2>Onboard Led schalten</h2>
    <h3>ESP32 Dev Module</h3>
    <p>LED ist %s<p>
    <form action="/led">
      <input name="led" type="submit" value="LED %s">
    </form>
  </body>
</html>)", digitalRead(LED_BUILTIN) ? "an" : "aus", digitalRead(LED_BUILTIN) ? "Aus" : "Ein");
  server.send(200, "text/html", temp);
}

void espboardLed() {
  pinMode(LED_BUILTIN, OUTPUT);     // OnBoardLed Esp32
  server.on ( "/led", esp32Led );
  digitalWrite(LED_BUILTIN,HIGH);
}
void onboardLed() {
  pinMode(LED_BUILTIN, OUTPUT);     // OnBoardLed Esp32
  server.on("/bled", []() {
    if (server.hasArg("zap")) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));    // LED umschalten
      DEBUG_P(digitalRead(LED_BUILTIN) ? "LED ist an" : "LED ist aus");
    }
    server.send(200, "/onboardled.html", digitalRead(LED_BUILTIN) ? "Aus" : "Ein");
  });
}
void schaltuhr(){

constexpr auto ACTIVE = LOW;                                             // LOW für LOW aktive Relais oder HIGH für HIGH aktive (zB. SSR, Mosfet) einstellen
constexpr uint8_t DEVICE_PIN = T7;                                       // Pin für Device einstellen
constexpr uint8_t RECORDS = 20;                                          // Anzahl Schaltzeiten festlegen 1 - 100
bool pinState {!ACTIVE};

typedef char timeArr[6];
timeArr sunTime[4];

using namespace std;
using Subset = tuple<bool, uint8_t, String, String>;
vector<Subset> device;

struct extra {
  uint8_t sun;
  bool fixed;
} option;

void setupTimerSwitch() {
  digitalWrite(DEVICE_PIN, !ACTIVE);
  pinMode(DEVICE_PIN, OUTPUT);
  device.reserve(RECORDS);
  Subset t = make_tuple(1, 127, "", "");
  File file = LittleFS.open(existFolder("/Config") + "/stime.dat");
  if (file) {                                                            // Einlesen aller Daten falls die Datei im LittleFS vorhanden und deren Größe stimmt.
    file.read(reinterpret_cast<uint8_t*>(&option), sizeof(option));
    for (uint8_t i = 0; i < device.capacity(); i++) {
      file.read(reinterpret_cast<uint8_t*>(&t), sizeof(Subset));
      device.emplace_back(t);
    }
    file.close();
#ifdef DEBUGGING
    uint8_t j = 0;
    for (const auto &e : device) DEBUG_F(PSTR("Subset %d: %d, %d, %s, %s\n"), ++j, get<0>(e), get<1>(e), get<2>(e).c_str(), get<3>(e).c_str());
#endif
  }
  else {
    DEBUG_F(F("Die \"stime.dat\" ist nicht vorhanden!"));
    for (uint8_t i = 0; i < device.capacity(); i++) device.push_back(t);
  }
  DEBUG_F(PSTR("\nZeitschaltuhr Automatik %saktiviert\n\n"), option.fixed ? "de" : "");
  server.on("/timer", HTTP_POST, []() {
    if (server.hasArg("dTime")) {
      device.clear();
      Subset t = make_tuple(0, 0, "", "");
      char str[server.arg("dTime").length()];
      strcpy (str, server.arg("dTime").c_str());
      char* ptr = strtok(str, "[\"");
      for (auto i = 0; ptr != NULL; i++, i %= 4) {
        if (strcmp(ptr, ",")) {
          if (i == 0) {
            get<0>(t) = atoi(ptr);
          }
          else if (i == 1) {
            get<1>(t) = atoi(ptr);
          }
          else if (i == 2) {
            get<2>(t) = static_cast<String>(ptr);
          }
          else if (i == 3) {
            get<3>(t) = static_cast<String>(ptr);
            device.emplace_back(t);
          }
        }
        ptr = strtok(NULL, "\",[]");
      }
      printer();
    }
    String temp = "[";
    for (auto &t : device) {
      temp == "[" ? temp += "[" : temp += ",[";
      temp += "\"" + static_cast<String>(get<0>(t)) + "\",";
      temp += "\"" + static_cast<String>(get<1>(t)) + "\",";
      temp += "\"" + get<2>(t) + "\",";
      temp += "\"" + get<3>(t) + "\"]";
    }
    temp += "]";
    server.send(200, "application/json", temp);
  });
  server.on("/timer", HTTP_GET, []() {
    char buf[44];
    if (server.arg(0) == "tog") {
      pinState = !pinState;                                              // Pin Status manuell ändern
      timeDataLogger(ACTIVE, pinState, server.client().remoteIP().toString());   // Funktionsaufruf Zeitdatenlogger
    }
    else if (server.arg(0) == "fix") {
      option.fixed = !option.fixed;                                      // alle Schalzeiten deaktivieren/aktivieren
      printer();
    }
    if (server.arg(0) == "sun") {
      if (server.hasArg("select")) {
        option.sun = server.arg(1).toInt();
        printer();
      }
      snprintf(buf, sizeof(buf), "[[\"%s\",\"%s\",\"%s\",\"%s\"],[\"%d\"]]", sunTime[0], sunTime[1], sunTime[2], sunTime[3], option.sun);
    }
    else {
      snprintf(buf, sizeof(buf), "[\"%d\",\"%s\",\"%d\"]", pinState == ACTIVE, localTime(), option.fixed);
    }
    server.send(200, "application/json", buf);
  });
}

void printer() {
  File file = LittleFS.open(existFolder("/Config") + "/stime.dat", "w");
  if (file) {
    file.write(reinterpret_cast<const uint8_t*>(&option), sizeof(option));
    for (const auto &e : device) {
      file.write(reinterpret_cast<const uint8_t*>(&e), sizeof(e));
    }
    file.close();
  }
}

void timerSwitch() {
  static uint8_t lastmin {CHAR_MAX}, lastState {ACTIVE};
  hobbsMeter(pinState);                                                  // Funktionsaufruf Betriebsstundenzähler mit Pin Status
  button(pinState);                                                      // Funktionsaufruf Manueller Taster mit Pin Status
  timeDataLogger(ACTIVE, pinState, "Taster");                            // Funktionsaufruf Zeitdatenlogger
  if (tm.tm_min != lastmin && !option.fixed) {
    lastmin = tm.tm_min;
    char buf[6];
    sprintf(buf, "%.2d:%.2d", tm.tm_hour, tm.tm_min);
    for (auto &t : device) {
      if (get<0>(t) && (get<1>(t) & (1 << (tm.tm_wday ? tm.tm_wday - 1 : 6)))) {
        if (!get<2>(t).compareTo(buf)) pinState = ACTIVE;
        if (!get<3>(t).compareTo(buf)) pinState = !ACTIVE;
      }
    }
    for (auto i = 0; i < 4; i++) {
      if (!strcmp(sunTime[i], buf)) {                                    // Pin Status zum Sonnenstand ändern
        if (option.sun & (1 << i * 2)) pinState = !ACTIVE;
        if (option.sun & (1 << (i * 2 + 1))) pinState = ACTIVE;
      }
    }
    timeDataLogger(ACTIVE, pinState, "Programm");                        // Funktionsaufruf Zeitdatenlogger
  }
  if (pinState != lastState) {                                           // Pin schalten wenn sich der Status geändert hat
    lastState = pinState;
    digitalWrite(DEVICE_PIN, pinState);
    DEBUG_F(PSTR("Schaltausgang A%s\n"), digitalRead(DEVICE_PIN) == ACTIVE ? "n" : "us");
  }
}



}
void setup() {
  pinMode(ledPin4,OUTPUT);
  pinMode(ledPin5,OUTPUT);
  digitalWrite(ledPin4,HIGH);
  digitalWrite(ledPin5,HIGH);
  DEBUG_B(115200);
  DEBUG_F("\nSketchname: %s\nBuild: %s\t\tIDE: %d.%d.%d\n\n", __FILE__, __TIMESTAMP__, ARDUINO / 10000, ARDUINO % 10000 / 100, ARDUINO % 100 / 10 ? ARDUINO % 100 : ARDUINO % 10);
  
  //setupFS();
  Connect();
  //admin();
 // setupTime();
  espboardLed();
  onboardLed();
  //  bme280();
  //  dht22();                      // Die Tabs die du nutzen möchtest, musst du Einkommentieren
  //  bh1750();
  //  setupSchaltUhr();

  ArduinoOTA.onStart([]() {
    //save();                       //Einkommentieren wenn Werte vor dem Update gesichert werden sollen
  });
  ArduinoOTA.begin();

  server.begin();
  DEBUG_P("HTTP Server gestartet\n\n");
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
  digitalWrite(ledPin4,LOW);
  digitalWrite(ledPin5,LOW);
  delay(250);
  digitalWrite(ledPin4,HIGH);
  digitalWrite(ledPin5,HIGH);
  delay(250);
  Serial.println("Esp32 IP: " + WiFi.localIP().toString() + "\n");
  delay(1000);
  //if (millis() < 0x2FFF || millis() > 0xFFFFF0FF) runtime();  // Auskommentieren falls du den Admin Tab nicht nutzen möchtest
  //  emailResponse();
  //  dualSchaltuhr();				// Die Tabs die du nutzen möchtest, musst du Einkommentieren
}