#ifndef myLeds_h
#define myLeds_h
#include <Arduino.h>

class myLeds
{
    public:
        myLeds(int pina,int pinb,int pinc,int pind);
        void begin();
            
             
    private:
           int _pina; 
           int _pinb;
           int _pinc;
           int _pind;
 
};




#endif