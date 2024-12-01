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
    tempSensor->init();
    lastDataSentTime = 0;
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
        if (prevTemperature > 29.0) {
            door->close();
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
        state = NORMAL_TEMPERATURE;
        break;
    }
}