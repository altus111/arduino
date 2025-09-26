#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "DHT.h" //DHT Bibliothek laden
#define DHTPIN 2 //Der Sensor wird an PIN 2 angeschlossen    
#define DHTTYPE DHT11    // Es handelt sich um den DHT11 Sensor

DHT dht(DHTPIN, DHTTYPE); //Der Sensor wird ab jetzt mit „dth“ angesprochen


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

int blinkPin1=9;
int blinkPin=8;
int cursorStart[2] = {0,0};
void setup() {
  Serial.begin(9600);
  display.begin();
  display.setRotation(90);
  pinMode(blinkPin1,OUTPUT);
  pinMode(blinkPin,OUTPUT);
  
  display.setContrast(50);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(cursorStart[0],cursorStart[1]);
  display.println("Welcome!");
  display.display();
}
int i = 0;
void loop() {
  display.setCursor(cursorStart[0],cursorStart[1]);
  cursorStart[1] = i + 10;
  i = cursorStart[1];
  display.println("Welcome!");
  display.display();
  display.clearDisplay();
  digitalWrite(blinkPin,LOW);
  digitalWrite(blinkPin1,HIGH);
  delay(1000);
  digitalWrite(blinkPin,HIGH);
  digitalWrite(blinkPin1,LOW);
  delay(1000);

}

