#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino_LED_Matrix.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);  //Hier wird das Display benannt (Adresse/Zeichen pro Zeile/Anzahl Zeilen).
                                     //In unserem Fall „lcd“. Die Adresse des I²C Displays kann je nach Modul variieren.
ArduinoLEDMatrix Matrix;
int LEDrot = 5;
int LEDgruen = 6;
int LEDblau = 3;
int Pause = 500;      // Pause mit 1000ms also 1 Sekunde
int Helligkeit = 250;  // Zahlenwert zwischen 0 und 255 – gibt die Leuchtstärke der einzelnen Farbe an


byte PfeilLinks[8][12] = 
{
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte PfeilRechts[8][12] = 
{
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }
};
void loop0() 
{ Serial.println(__func__); 
  Matrix.renderBitmap(PfeilLinks, 8, 12);
  analogWrite(LEDrot, Helligkeit);   // rot einschalten
  delay(2000);
  analogWrite(LEDrot, LOW);
  Matrix.renderBitmap(PfeilRechts, 8, 12);
  delay(100);
}
void loop1() {
   Serial.println(__func__);
   Matrix.renderBitmap(PfeilRechts, 8, 12);
   delay(50);
   analogWrite(LEDrot, LOW);          // rot ausschalten
}
void loop2() 
{ Serial.println(__func__); 
  analogWrite(LEDblau, Helligkeit);
  delay(50);
  analogWrite(LEDblau, LOW);
  analogWrite(LEDgruen, Helligkeit);
  delay(50);
  analogWrite(LEDgruen, LOW);
}
void (*loops[]) () {loop0, loop1, loop2};

void setup() 
{
  Serial.begin(9600);
  pinMode(LEDblau, OUTPUT);
  pinMode(LEDgruen, OUTPUT);
  pinMode(LEDrot, OUTPUT);
  Matrix.begin();
  lcd.init();
  lcd.backlight();
 

}




void loop()
{
  Matrix.renderBitmap(PfeilLinks, 8, 12);
  delay(Pause);
  Matrix.renderBitmap(PfeilRechts, 8, 12);
  analogWrite(LEDrot, Helligkeit);   // rot einschalten
  delay(Pause);                      // Pause
  analogWrite(LEDrot, LOW);          // rot ausschalten
  analogWrite(LEDgruen, Helligkeit); // gruen einschalten
  delay(Pause);                      // Pause
  analogWrite(LEDgruen, LOW);        // gruen ausschalten
  analogWrite(LEDblau, Helligkeit);  // blau einschalten
  delay(Pause);                      // Pause
  analogWrite(LEDblau, LOW);         // blau ausschalten
  lcd.setCursor(0,2);
  lcd.print("Hallo Welt");
  lcd.scrollDisplayLeft();
 //for (auto loop_:loops) loop_(), delay(50);  // for testing only 
 //loop0();
 //delay(2000);
}


