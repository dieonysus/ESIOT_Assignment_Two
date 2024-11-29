#include "Temp.h"


TempSensor::TempSensor(int pin) : sensorPin(pin) {}

void TempSensor::init() {
    pinMode(sensorPin, INPUT);
}

float TempSensor::readTemperature() {
    int sensorValue = analogRead(sensorPin);
    
    float voltage = sensorValue * (5.0 / 1023.0);  
    float temperature = voltage * 100.0;          
    return temperature;
}