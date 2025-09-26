#include <Arduino.h>
#include "WiFi.h"
#include "time.h"
#include <SPI.h>

// SSID und Passwort des Routers
char Router[] = "UPC0128016";
char Passwort[] = "c9zxScwDnndq";
WiFiServer Server(80);
WiFiClient Client;
const char* NTP_SERVER = "ch.pool.ntp.org";
const char* TZ_INFO    = "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00";

char wochentage[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
String monat[12] = {"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"};

time_t now;
tm tm1;

int ledPinRed = 26;
int ledPinGreen = 27; 

void setup()
{
  Serial.begin(115200);
  pinMode(ledPinRed,OUTPUT);
  pinMode(ledPinGreen,OUTPUT);
  digitalWrite(ledPinRed,HIGH);
  digitalWrite(ledPinGreen,HIGH);
  delay(2000);
  // auf serielle Verbindung warten
  //*
  while (!Serial);
  // WiFi starten
  WiFi.begin(Router, Passwort);

  // Verbindung herstellen
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Server.begin();

  // SSID des Routers anzeigen
  Serial.println();
  Serial.print("Verbunden mit ");
  Serial.println(WiFi.SSID());

  // IP anzeigen
  Serial.println(WiFi.localIP());
  configTime(0, 0, NTP_SERVER);
  setenv("TZ", TZ_INFO, 1);
 //*/
}

void loop()
{

  Serial.print("Verbunden mit ");
  Serial.println(WiFi.SSID());
  delay(2000);
  Serial.print("local IP ");
  Serial.println(WiFi.localIP());
  delay(2000);
  
  digitalWrite(ledPinRed,HIGH);
  digitalWrite(ledPinGreen,LOW);
  delay(100);
  digitalWrite(ledPinRed,LOW);
  digitalWrite(ledPinGreen,HIGH);
  delay(100);
  
  time(&now);                       // Liest die aktuelle Zeit
  localtime_r(&now, &tm1);           // Beschreibt tm mit der aktuelle Zeit

  //Serial.printf("%02d.%02d.%02d-%02d.%02d.%04d \t",tm1.tm_hour,tm1.tm_min,tm1.tm_sec, tm1.tm_mday, tm1.tm_mon + 1, tm1.tm_year + 1900);
  Serial.printf("%02d %s %04d \t", wochentage[tm1.tm_mday], monat[tm1.tm_mon], tm1.tm_year + 1900);  // Monat ausgeschrieben

}