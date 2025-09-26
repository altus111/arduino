#include <Arduino.h>
#include <Wire.h>  // Wire Bibliothek hochladen
#include <LiquidCrystal_I2C.h> // Vorher hinzugefügte LiquidCrystal_I2C Bibliothek hochladen
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTTYPE DHT11 //#define DHTTYPE11 DHT22
#define DHTPIN 26 //Der Sensor wird an PIN 26 angeschlossen




DHT dht(DHTPIN, DHTTYPE); //
LiquidCrystal_I2C lcd(0x27, 20, 4);  //Hier wird das Display benannt (Adresse/Zeichen pro Zeile/Anzahl Zeilen). In unserem Fall „lcd“. Die Adresse des I²C Displays kann je nach Modul variieren.
int blinkPin = 27;
	
void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.init(); 
  lcd.backlight(); //zuerst Backlight einschalten
  
  
  pinMode(blinkPin,OUTPUT);
  digitalWrite(blinkPin,LOW);
 }

int i=0; //zaehlt die Anzahl Messungen
void loop() {
  i++;
  //lcd.clear();
  float feuchtigkeit =0;
  float temperatur =0;
  feuchtigkeit = dht.readHumidity(); //die Luftfeuchtigkeit auslesen und unter „Luftfeuchtigkeit“ speichern
  delay(50);
  temperatur = dht.readTemperature();//die Temperatur auslesen und unter „Temperatur“ speichern
  
  Serial.print(feuchtigkeit);
  Serial.println(" %");
  Serial.print(temperatur);
  Serial.println(" C");
  digitalWrite(blinkPin,HIGH);
  if (isnan(feuchtigkeit) || isnan(temperatur)) 
  {
    digitalWrite(blinkPin,LOW);
    lcd.clear();
    lcd.setCursor(8,2);
    lcd.print("Bitte warten.Werte werden neu gemessen.");
    lcd.display();
  } 
  
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DHT");
  lcd.print(DHTTYPE);
  lcd.print(" Messung ");
  lcd.setCursor(15,0);
  lcd.print(i);

  lcd.setCursor(0,1);
  lcd.print("--------------------");
 

  lcd.setCursor(0,2);
  lcd.print("Feuchtigkeit:");
  lcd.print(feuchtigkeit);

  lcd.setCursor(0,3);
  lcd.print("Temperatur:");
  lcd.print(temperatur);

  lcd.display();
  
}
