
// ****************************************************************
// Arduino IDE Tab Esp32 Lokalzeit Intervall Modular
// created: Jens Fleischer, 2024-03-06
// last mod: Jens Fleischer, 2024-03-06
// ****************************************************************
// Hardware: Esp32
// Software: Esp32 Arduino Core 2.0.0 - 2.0.14
// Getestet auf: ESP32 NodeMCU-32s
/******************************************************************
  Copyright (c) 2024 Jens Fleischer. All rights reserved.

  This file is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This file is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*******************************************************************/
// Diese Version von Lokalzeit sollte als Tab eingebunden werden.
// #include <WebServer.h> oder #include <WiFi.h> muss im Haupttab aufgerufen werden
// Funktion "setupTime();" muss im setup() nach dem Verbindungsaufbau aufgerufen werden.
/**************************************************************************************/
#include <WebServer.h>
#include "time.h"
#include "esp_sntp.h"

struct tm tm;


const char* const PROGMEM ntpServer[] = {"fritz.box", "de.pool.ntp.org", "at.pool.ntp.org", "ch.pool.ntp.org", "ptbtime1.ptb.de", "europe.pool.ntp.org"};
const char* const PROGMEM dayNames[] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
const char* const PROGMEM dayShortNames[] = {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};
const char* const PROGMEM monthNames[] = {"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"};
const char* const PROGMEM monthShortNames[] = {"Jan", "Feb", "Mrz", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"};


void setupTime() {
  /**
    Optional für den Individuellen SNTP Update Intervall. Standart ist aller 3 Stunden.
    Der Synchronisierungsintervall in ms. ES darf nicht kleiner als 15 Sekunden sein, andernfalls werden 15 Sekunden eingestellt.
  */
   // sntp_set_sync_interval(60000);

  sntp_set_time_sync_notification_cb([](struct timeval * t) {       // Rückruffunktion - wird aufgerufen, wenn SNTP Aktualisierung erfolgte.
    Serial.println("********* Zeitstempel vom NTP Server erhalten! *********");
  });

  // Serielle Ausgabe des NTP Update Intervall
  //Serial.println("SNTP Sync Interval: %02d:%02d:%02d\n", sntp_get_sync_interval() / 3600000 % 24, sntp_get_sync_interval() / 60000 % 60, sntp_get_sync_interval() / 1000 % 60);

  // Zeitzone einstellen https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
  configTzTime("CET-1CEST,M3.5.0/02,M10.5.0/03", ntpServer[1]);     // Es können durch Komma getrennt bis zu 3 NTP Server eingegeben werden.

  //server.on("/time", []() {
  //  server.send(200, "application/json",  localTime());
//  });
}

char* localTime() {
  static char buf[22];                                              // je nach Format von "strftime" eventuell die Größe anpassen
  getLocalTime(&tm, 500);

  /** Beispiele
    DEBUG_P(dayNames[tm.tm_wday]);               // druckt den aktuellen Tag
    DEBUG_P(monthNames[tm.tm_mon]);              // druckt den aktuellen Monat
    DEBUG_P(dayShortNames[tm.tm_wday]);          // druckt den aktuellen Tag (Abk.)
    DEBUG_P(monthShortNames[tm.tm_mon]);         // druckt den aktuellen Monat (Abk.)
    DEBUG_P(tm.tm_isdst ? "Sommerzeit" : "Normalzeit");
  */
  
  strftime (buf, sizeof(buf), "\"%d.%m.%Y %T\"", &tm);              // http://www.cplusplus.com/reference/ctime/strftime/
  return buf;
}

