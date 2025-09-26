#include <Arduino.h>
#include "WiFi.h"
//#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "time.h"
#include "WebServer.h"
#include "ArduinoOTA.h"
#include "esp_sntp.h"

const char* ssid = "UPC0128016";             // Network name.
const char* password = "c9zxScwDnndq";            // Password network.
WebServer server(80);

uint8_t LED1pin = 4;
bool LED1status = LOW;
uint8_t LED2pin = 5;
bool LED2status = LOW;


// Zeit
struct tm tm;
const char* const PROGMEM ntpServer[] = {"fritz.box", "de.pool.ntp.org", "at.pool.ntp.org", "ch.pool.ntp.org", "ptbtime1.ptb.de", "europe.pool.ntp.org"};
const char* const PROGMEM monthShortNames[] = {"Jan", "Feb", "Mrz", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"};

void setupTime() {
  sntp_set_time_sync_notification_cb([](struct timeval * t) {
    Serial.println("********* Zeitstempel vom NTP Server erhalten! *********");
  });
  configTzTime("CET-1CEST,M3.5.0/02,M10.5.0/03", ntpServer[1]);    // deinen NTP Server einstellen (von 0 - 5 aus obiger Liste)
}

char* localTime() {
  static char buf[10];                                             // je nach Format von "strftime" eventuell die Größe anpassen
  getLocalTime(&tm);
  strftime (buf, sizeof(buf), "%T", &tm);                          // http://www.cplusplus.com/reference/ctime/strftime/
  return buf;
}
// Ende Zeit


String SendHTML(uint8_t led1stat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +=".button-blink {background-color: #34495e;}\n";
  ptr +=".button-blink:active {background-color: #2c3e50;}\n";  
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP32 Web Server</h1>\n";
  ptr +="<h3>Using Station(STA) Mode</h3>\n";
  
  if(led1stat)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

void Connect() {                                 // Funktionsaufruf "Connect();" muss im Setup nach "spiffs();" eingebunden werden
  pinMode(LED_BUILTIN, OUTPUT);                  // OnBoardLed ESP32 Dev Module
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, 1);
    delay(250);
    digitalWrite(LED_BUILTIN, 0);
    delay(250);
    
    if (millis() > 10000) {
      Serial.print("\nVerbindung zum AP fehlgeschlagen\n\n");
      ESP.restart();
    }
  }
  Serial.print("\nVerbunden mit: " + WiFi.SSID());
  Serial.print("Esp32 IP: " + WiFi.localIP().toString() + "\n");
}
void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  Serial.println("GPIO4 Status: OFF | GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status)); 
}
void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO4 Status: ON");
  digitalWrite(LED1pin,HIGH);
  server.send(200, "text/html", SendHTML(true,LED2status)); 
}

void handle_led1off() {
  LED1status = LOW;
  digitalWrite(LED1pin,LOW);
  Serial.println("GPIO4 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status)); 
}

void handle_led2on() {
  LED2status = HIGH;
  digitalWrite(LED2pin,HIGH);
  Serial.println("GPIO5 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,true)); 
}

void handle_led2off() {
  LED2status = LOW;
  digitalWrite(LED2pin,LOW);
  Serial.println("GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,false)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Kein Anschluss unter dieser Nummer");
}
void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED,OUTPUT);
  
  pinMode(LED1pin,OUTPUT);
  pinMode(LED2pin,OUTPUT);
  Connect();
  ArduinoOTA.onStart([]() {
    //save();                       //Einkommentieren wenn Werte vor dem Update gesichert werden sollen
  });
  ArduinoOTA.begin();
  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
  localTime();

}


void loop() {
  ArduinoOTA.handle();
  server.handleClient();  
  digitalRead(LED1pin);
  Serial.println("Led1 ");
  Serial.println();
  digitalRead(LED2pin);
  Serial.println("Led2 " + LED1status);
  delay(1000);
  int delaytime(300);
  digitalWrite(BUILTIN_LED,HIGH);
  delay(delaytime);
  /*
  digitalWrite(LED1pin,HIGH);
  delay(500);
  digitalWrite(LED2pin,HIGH);
  delay(500);
  digitalWrite(LED1pin,LOW);
  delay(500);
  digitalWrite(LED2pin,LOW);
  delay(500);
  */  
  digitalWrite(BUILTIN_LED,LOW);
  delay(delaytime);
}
