#include <Dice.h>
#include <Arduino.h>
#define DEBUG

int allLeds[3];
Dice::Dice(int led4, int led2, int led1) {
  _led4 = led4; // LED that represents MSBit
  _led2 = led2; // LED that represents medium Bit
  _led1 = led1;
  pinMode(_led4, OUTPUT); // all pins are OUTPUT pins
  pinMode(_led2, OUTPUT);
  pinMode(_led1, OUTPUT);
  
  randomSeed(analogRead(A0)); // random value from analog A0 for 
                              // initial seed
}

void Dice::roll() {

   int result = random(1,7); // get a random number from 1..6

#ifdef DEBUG
   Serial.print("dice value = ");
   Serial.println(result);
#endif

//start led4
   controlLED(_led4, (1 == result / 4 )); // simple arithmetic
   //all[0] = result;
#ifdef DEBUG
   Serial.print("LED4 = ");
   Serial.println(1 == result / 4);
   allLeds[0] = result / 4; 
#endif
//end led4

// start led2
   result = result % 4;
   controlLED(_led2, (1 == result /  2));
   allLeds[1] = result / 2;  
#ifdef DEBUG
   Serial.print("LED2 = ");
   Serial.println(1 == result / 2);
#endif
//end led2

//start led1
   result = result % 2;
   controlLED(_led1, 1 ==  result);
   allLeds[2] = result % 2;
#ifdef DEBUG
   Serial.print("LED1 = ");
   Serial.println(1 == result);
#endif
// end led1
}

void Dice::SetAllLeds(){

   Serial.print("Resultat: ");
   digitalWrite(_led1,allLeds[0]);
   digitalWrite(_led2,allLeds[1]);
   digitalWrite(_led4,allLeds[2]);
   delay(1000);

}
void Dice::begin(){
      digitalWrite(_led1,1);
      digitalWrite(_led2,1);
      digitalWrite(_led4,1);
      delay(1000);
      digitalWrite(_led1,0);
      digitalWrite(_led2,0);
      digitalWrite(_led4,0);
}
void Dice::controlLED(int led, bool on) {
  if (on)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);
}
