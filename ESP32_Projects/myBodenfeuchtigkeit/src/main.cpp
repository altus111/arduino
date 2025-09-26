#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Preferences.h>
#include <PubSubClient.h>
#include <time.h>
#include <FS.h>
#define SCREEN_I2C_ADDR 0x3c // or 0x3C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
const unsigned long calibrationPeriod = 20000;  // Kalibrierungszeit in Millisekunden (20 Sekunden)
const unsigned long sleepTimeSeconds = 20;  // Schlafzeit des Sensors in Sekunden (hier auf 20 Sekunden gesetzt)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int blinkPin = BUILTIN_LED;
int SensorPin1 = 34; //ADC1-Pins funktionieren auch mit WiFi
int SensorPin2 = 35;
int SensorPin2 = 36;
WiFiClient espClient;
PubSubClient client(espClient);
//Preferences preference();

void internalDisplay(){
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
   display.clearDisplay();
   delay(500);
}
double Prozent(int MessVal,int AbsVal){
  double tmpmess = 100 * MessVal / AbsVal;
  return tmpmess;

}
void Bodenfeuchte(int zaehler,int sensorpin){
  int txtSize = 1;
  int MessData = 0;
  int messStep = 3000;
  int luft = 0; 
  int wasser = 2400; // wenn der Sensor komplett in Wasser getaucht wird 100%.
  digitalWrite(blinkPin,HIGH);
  display.clearDisplay();
  MessData = analogRead(sensorpin);
  delay(500);
  display.setTextColor(WHITE); display.setTextSize(1.1);
  display.setCursor(0,0);
  display.print("Feuchtigkeit 100% =");
  display.setCursor(0,15);display.print(wasser);

  display.setTextColor(WHITE); display.setTextSize(txtSize);
  display.setCursor(0,30);display.setTextSize(0.8);
  display.print("Zaehler: ");display.print(zaehler);
  display.setCursor(0,40);
  display.print("Messung absolut: ");display.print(MessData);
  display.setCursor(0,50);
  display.print("Messung in % ");display.print(Prozent(MessData,wasser));
  display.display();
  delay(messStep);
  digitalWrite(blinkPin,LOW);
  delay(1000);

}
void Wifi_OtaConnect(){
  const char* ssid = "UPC0128016";             // Network name.
  const char* password = "c9zxScwDnndq";            // Password network.
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  ArduinoOTA.setHostname("myEsp32");
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
      } else {  // U_SPIFFS
        type = "filesystem";
      }
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) {
        Serial.println("Auth Failed");
      } else if (error == OTA_BEGIN_ERROR) {
        Serial.println("Begin Failed");
      } else if (error == OTA_CONNECT_ERROR) {
        Serial.println("Connect Failed");
      } else if (error == OTA_RECEIVE_ERROR) {
        Serial.println("Receive Failed");
      } else if (error == OTA_END_ERROR) {
        Serial.println("End Failed");
      }
    });

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  ArduinoOTA.begin();

}


void setup() {
  Serial.begin(115200);
  Wifi_OtaConnect();
  internalDisplay();
  pinMode(blinkPin,OUTPUT);
  digitalWrite(blinkPin,HIGH);
}

int i = 0;
void loop() {
  
  ArduinoOTA.handle();
  Bodenfeuchte(i,SensorPin1);

  i++;
}
