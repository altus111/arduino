
// ****************************************************************
// Arduino IDE Tab Esp32 SNTP Lokalzeit Mini Modular
// created: Jens Fleischer, 2024-03-04
// last mod: Jens Fleischer, 2024-03-06
// ****************************************************************
// Hardware: Esp32
// Software: Esp32 Arduino Core 1.0.0 - 2.0.14
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
// #include <WebServer.h> muss im Haupttab aufgerufen werden.
// Funktion "setupTime();" muss im setup() nach dem Verbindungsaufbau aufgerufen werden.
/**************************************************************************************/

#include "time.h"
/*
void setupTime() {
  configTzTime("CET-1CEST,M3.5.0,M10.5.0/3", "fritz.box", "de.pool.ntp.org");
  server.on("/time", []() {
    struct tm tm;
    getLocalTime(&tm);
    static char buf[22];
    strftime (buf, sizeof(buf), "\"%d.%m.%Y %T\"", &tm);   // http://www.cplusplus.com/reference/ctime/strftime/
    server.send(200, "application/json", buf);
  });
}
*/
