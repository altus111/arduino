#include <Arduino.h>
//#include <WiFiS3.h>
#include <WiFi.h>
//#include <WiFiNINA.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino_LED_Matrix.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);  //Hier wird das Display benannt (Adresse/Zeichen pro Zeile/Anzahl Zeilen).
                                     //In unserem Fall „lcd“. Die Adresse des I²C Displays kann je nach Modul variieren.
ArduinoLEDMatrix Matrix;
int LedGruen = 7;
int LedRot = 8;
int LedBlau = 9;
void WriteLcd(String,int);
void WifiConnect(){
  while (!Serial);
    const char* ssid = "UPC0128016";             // Network name.
    const char* password = "c9zxScwDnndq";            // Password network.
    Serial.println("Starte WiFi-Test...");

    // Mit WLAN verbinden
    WiFi.begin(ssid, password);

    Serial.print("Verbinde mit WLAN");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
 
    WriteLcd("WLAN verbunden!",0);
    WriteLcd("IP-Adresse: ",1);
    WriteLcd("Test",2);
    Serial.write(WiFi.localIP());

}
void WriteLcd(String text,int line){

  lcd.setCursor(0,line);
  lcd.print(text);
}
void setup() {
  Serial.begin(9600);
  WifiConnect();
  lcd.init();
  lcd.backlight();  
  pinMode(LedGruen, OUTPUT);
  pinMode(LedRot, OUTPUT);
  pinMode(LedBlau, OUTPUT);
  digitalWrite(LedRot,HIGH);
}

void loop() {
/*
    if (Serial.available()){
        String cmd = Serial.readString();
        Serial.print("CMD:");
        Serial.println(cmd);      
      if (cmd == "1"){
        digitalWrite(LedGruen,HIGH);
      }else if (cmd == "0"){
        digitalWrite(LedRot,HIGH);
      }else if (cmd == "2"){
        digitalWrite(LedGruen,LOW);
        digitalWrite(LedRot,LOW);
      }else {
        //digitalWrite(LedGruen,LOW);
        //digitalWrite(LedRot,LOW);
      }
  } else {Serial.println("Serial nicht verfügbar");}
  
  Serial.println("Ende"); 
  delay(2000);
*/
}

