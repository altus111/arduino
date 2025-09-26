
#ifndef myBlinken_h
#define myBlinken_h
#include <Arduino.h>
class myBlinken
{

    
    public:
        //myBlinken(int pin,int pin1,int pin2,int wait); //Pin-Nummer,Delay
        myBlinken(int pin,int wait); //Pin-Nummer,Delay
        void begin();
        void blink();
    protected:
        
        int _pin;
        //int _pin1;
        //int _pin2;
        int _wait; 
 
 
        
 

};
#endif


