#include "TemperatureMonitoringTask.h"
#include "MsgService.h"
#include "shared.h"

#define TEMP_SENSOR_PIN A0

TemperatureMonitoringTask::TemperatureMonitoringTask(Lcd* lcd, ServoMotor* door, Led* greenLed, Led* redLed) {
    this->lcd = lcd;
    this->door = door;
    this->greenLed = greenLed;
    this->redLed = redLed;
}

void TemperatureMonitoringTask::init(int period) {
    Task::init(period);

    tempSensor = new TempSensor(TEMP_SENSOR_PIN);
    tempSensor->init();

    lastDataSentTime = 0;

    state = NORMAL_TEMPERATURE;
}

void TemperatureMonitoringTask::tick() {

    unsigned long currentTime = millis();
    float currentTemp = tempSensor->readTemperature();
    if (currentTime - lastDataSentTime >= 500) {
        lastDataSentTime = currentTime;
        prevTemperature = currentTemp;
        MsgService.sendTemp(currentTemp);
    }


    switch (state) {
    case NORMAL_TEMPERATURE:
        if (prevTemperature > 30.0) {
            door->close();
            temperatureIsTooHigh = true;
            state = TEMPERATURE_PROBLEM;
        }
        break;
    
    case TEMPERATURE_PROBLEM:
        greenLed->switchOff();
        redLed->switchOn();
        lcd->updateLine(0, "PROBLEM DETECTED");
        lcd->updateLine(1, "");
        if (MsgService.isMsgAvailable()) {
            Msg* msg = MsgService.receiveMsg();
            if (msg->getContent() == "restore"){
                delay(100);
                state = RESTORING;
            }
        }
        break;
    
    case RESTORING:
        redLed->switchOff();
        greenLed->switchOn();
        temperatureIsTooHigh = false;
        state = NORMAL_TEMPERATURE;
        break;
    }
}