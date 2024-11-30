#include "TemperatureMonitoringTask.h"

TemperatureMonitoringTask::TemperatureMonitoringTask(Lcd* lcd, ServoMotor* door, Led* greenLed, Led* redLed) {
    this->lcd = lcd;
    this->door = door;
    this->greenLed = greenLed;
    this->redLed = redLed;
}

void TemperatureMonitoringTask::init(int period) {
    Task::init(period);
    state = NORMAL_TEMPERATURE;
    tempSensor = new TempSensor(A0);
}

void TemperatureMonitoringTask::tick() {
    redLed->switchOn();
    delay(1000);
    redLed->switchOff();
    
    switch (state) {

    case NORMAL_TEMPERATURE:
        break;
    
    case TEMPERATURE_PROBLEM:
        break;
    
    case RESTORING:
        break;
    }
}