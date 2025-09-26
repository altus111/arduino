#ifndef Morse_h
#define Morse_h
#include <Arduino.h>
class Morse
{
    public:
        Morse(int Pin);
        void begin();
        void dot();
        void dash();
    private:
        int _pin;

};
#endif