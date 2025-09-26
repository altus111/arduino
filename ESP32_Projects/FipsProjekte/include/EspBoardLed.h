#include <Arduino.h>
#include <WebServer.h>
WebServer server(80);
void espboardLed() {
  pinMode(LED_BUILTIN, OUTPUT);     // OnBoardLed Esp32
  server.on ( "/led", esp32Led );
}

void esp32Led() {                  //Html Seite
  if (server.hasArg("led")) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));        // LED umschalten
    //DEBUG_P(digitalRead(LED_BUILTIN) ? "LED ist aus" : "LED ist an");
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

