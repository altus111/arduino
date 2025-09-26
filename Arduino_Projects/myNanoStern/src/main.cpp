#include <Arduino.h>
#include <ArduinoOTA.h>
#include <WiFiUdp.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <SPIFFS.h>
const char* ssid = "UPC0128016";             // Network name.
const char* password = "c9zxScwDnndq";            // Password network.

AsyncWebServer server(80);
int Pin9 = 32;
int Pin11 = 33;
int Pin12 = 25;
int controlPin = 27;


void setup() {
  Serial.begin(115200);
  pinMode(controlPin,OUTPUT);
  digitalWrite(controlPin,LOW);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  /*
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP32.");
  });
  server.begin();
  */
  ArduinoOTA.begin();
}
void loop() {
  ArduinoOTA.handle();
  digitalWrite(controlPin,HIGH);
  delay(1000);
  digitalWrite(controlPin,LOW);
  delay(1000);
/*
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  delay(1000);
  */
}