#include <Arduino.h>
#include "DHT.h" //DHT Bibliothek laden
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define DHTPIN 2 //Der Sensor wird an PIN 2 angeschlossen    
#define DHTTYPE DHT11    // Es handelt sich um den DHT11 Sensor

DHT dht(DHTPIN, DHTTYPE); //Der Sensor wird ab jetzt mit „dth“ angesprochen
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);


int blinkPin=8;
void setup() {
  Serial.begin(9600); //Serielle Verbindung starten
  pinMode(blinkPin,OUTPUT);
  display.begin();
  display.setRotation(90);
  display.setContrast(50);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Welcome!");
  display.display();
  dht.begin(); //DHT11 Sensor starten
}

void loop() {
  delay(2000); //Zwei Sekunden Vorlaufzeit bis zur Messung (der Sensor ist etwas träge)
  digitalWrite(blinkPin,HIGH);
  delay(500);
  digitalWrite(blinkPin,LOW);
  delay(500);
  display.clearDisplay();
  float Luftfeuchtigkeit = dht.readHumidity(); //die Luftfeuchtigkeit auslesen und unter „Luftfeuchtigkeit“ speichern
  float Temperatur = dht.readTemperature();//die Temperatur auslesen und unter „Temperatur“ speichern
  display.print("Luftfeuchtigkeit: "); //Im seriellen Monitor den Text und 
  display.print(Luftfeuchtigkeit); //die Dazugehörigen Werte anzeigen
  display.println(" %");
  display.print("Temperatur: ");
  display.print(Temperatur);
  display.println(" Grad Celsius");
  display.display();

}
