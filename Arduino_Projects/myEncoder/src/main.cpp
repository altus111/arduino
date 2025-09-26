#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Encoder.h>

#define Clk_Pin 33
#define Sw_Pin 32
#define Dt_Pin 14
int Direction_Cw = 0;
int Direction_Ccw = 1;
int pushButton = 0;

LiquidCrystal_I2C lcd(0x27, 20, 4);

volatile int counter = 0;
long prev_counter;
volatile int direction = Direction_Cw;
volatile unsigned long last_time;  // for debouncing


ESP32Encoder encoder;

void setup() {
  Serial.begin(115200);
  encoder.attachHalfQuad ( Dt_Pin, Clk_Pin );
  encoder.setCount ( 0 );  
  lcd.init(); 
  lcd.backlight(); //zuerst Backlight einschalten
  

}

void loop() {
  
  counter = encoder.getCount() / 2;
  Serial.print("counter ");
  Serial.println(counter);
    lcd.clear();
    lcd.setCursor(0,2);
    lcd.print("Counter ");
    lcd.setCursor(8,2);
    lcd.print(counter);
    lcd.display();
  if (counter <0){
            Direction_Ccw = 1; 
            Direction_Cw = 0;
            Serial.println("Ccw links");
  }
  if (counter >0){
            Direction_Ccw = 0; 
            Direction_Cw = 1;
            Serial.println("Cw rechts");
  }
  delay(500);
 

}

