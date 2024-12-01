#include "TemperatureMonitoringTask.h"
#include "MsgService.h"

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
    lastDataSentTime = 0;
}

void TemperatureMonitoringTask::tick() {
    unsigned long currentTime = millis();
    if (currentTime - lastDataSentTime >= 1000) {
        lastDataSentTime = currentTime;
        MsgService.sendTemp(36.6);
    }


    switch (state) {

    case NORMAL_TEMPERATURE:
        break;
    
    case TEMPERATURE_PROBLEM:
        break;
    
    case RESTORING:
        break;
    }
}