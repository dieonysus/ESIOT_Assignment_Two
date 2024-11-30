#ifndef __TEMPSENSOR__
#define __TEMPSENSOR__

#include "Arduino.h"

class TempSensor {
public:
    TempSensor(int pin);  
    void init();             
    float readTemperature();  

private:
    int sensorPin;        
};

#endif