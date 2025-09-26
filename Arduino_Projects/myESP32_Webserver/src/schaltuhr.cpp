// ****************************************************************
// Arduino IDE Tab Esp32 Schaltuhr Modular
// created: Jens Fleischer, 2020-09-05
// last mod: Jens Fleischer, 2024-03-06
// For more information visit: https://fipsok.de
// ****************************************************************
// Hardware: Esp32, Relais Modul o. Mosfet IRF3708 o. Fotek SSR-40 DA
// für Relais Modul
// GND an GND
// IN an T7 = GPIO 27
// VCC an VIN -> je nach verwendeten Esp.. möglich
// Jumper JD-VCC VCC
// alternativ ext. 5V Netzteil verwenden
//
// für Mosfet IRF3708
// Source an GND
// Mosfet Gate an T7 = GPIO 27
//
// für 3V Solid State Relais
// GND an GND
// SSR Input + an T7 = GPIO 27
//
// Software: Esp32 Arduino Core 2.0.6 - 2.0.14
// Getestet auf: ESP32 NodeMCU-32s
/******************************************************************
  Copyright (c) 2020 Jens Fleischer. All rights reserved.

  This file is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This file is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*******************************************************************/
// Diese Version von Zeitschaltuhr sollte als Tab eingebunden werden.
// #include <LittleFS.h> #include <WebServer.h> müssen im Haupttab aufgerufen werden
// Die Funktionalität des ESP32 Webservers ist erforderlich.
// Der Lokalzeit Tab ist zum ausführen der Zeitschaltuhr einzubinden.
// Die Funktion "setupTimerSwitch();" muss im Setup aufgerufen werden.
// Zum schalten muss die Funktion "timerSwitch();" im loop(); aufgerufen werden.
/**************************************************************************************/
#include <Arduino.h>
#include <tuple>
#include <vector>

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

