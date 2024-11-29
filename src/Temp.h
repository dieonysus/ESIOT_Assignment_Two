#ifndef __TEMP__
#define __TEMP__

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