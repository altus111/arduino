#include <Arduino.h>
#include <Wire.h>  // Wire Bibliothek hochladen
#include <LiquidCrystal_I2C.h> // Vorher hinzugefügte LiquidCrystal_I2C Bibliothek hochladen
LiquidCrystal_I2C lcd(0x27, 20, 4);  //Hier wird das Display benannt (Adresse/Zeichen pro Zeile/Anzahl Zeilen). In unserem Fall „lcd“. Die Adresse des I²C Displays kann je nach Modul variieren.

void setup()
{
lcd.init(); //Im Setup wird der LCD gestartet
lcd.backlight(); //Hintergrundbeleuchtung einschalten (0 schaltet die Beleuchtung aus).
Serial.begin(9600);
}
int i=1;
char buf[100];
void loop()
{

lcd.setCursor(0,0); //Text soll beim ersten Zeichen in der ersten Reihe beginnen..
sprintf(buf,"Zeile %d",i);
lcd.print(buf); //In der ersten Zeile soll der Text „Test Zeile 1“ angezeigt werden
delay(1000);
lcd.setCursor(0,1); //Text soll beim ersten Zeichen in der ersten Reihe beginnen..
sprintf(buf,"Zeile %d",i+1);
lcd.print(buf); //In der ersten Zeile soll der Text „Test Zeile 1“ angezeigt werden
delay(1000);
lcd.setCursor(0,2); //Text soll beim ersten Zeichen in der ersten Reihe beginnen..
sprintf(buf,"Zeile %d",i+2);
lcd.print(buf); //In der ersten Zeile soll der Text „Test Zeile 1“ angezeigt werden
delay(1000);
lcd.setCursor(0,3); //Text soll beim ersten Zeichen in der ersten Reihe beginnen..
sprintf(buf,"Zeile %d",i+3);
lcd.print(buf); //In der ersten Zeile soll der Text „Test Zeile 1“ angezeigt werden
delay(1000);
lcd.clear();
delay(1000);
}