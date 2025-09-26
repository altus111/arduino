#ifndef Dice_h
#define Dice_h
#include <Arduino.h>


// Simple class that defines a binary dice using 3 Bits
// with each of the Bits representing a digit of the binary number
// with a decimal value from 1..6
class Dice {
 public:
   Dice(int led4, int led2, int led1); // initialized with Pins
   void roll(); // roll the dice
   void begin();
   void SetAllLeds(); 
 private:
   int _led4; // LED representing bit 2
   int _led2; // LED representing bit 1
   int _led1; // LED representing bit 0
   void controlLED(int led, bool on); // internal method to turn LED on/off

   
};












#endif