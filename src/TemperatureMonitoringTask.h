#ifndef __TEMPERATUREMONITORINGTASK__
#define __TEMPERATUREMONITORINGTASK__

#include "Task.h"
#include "TempSensor.h"
#include "Lcd.h"
#include "ServoMotor.h"
#include "Led.h"

class TemperatureMonitoringTask : public Task {

    private:
        enum State {
            NORMAL_TEMPERATURE,
            TEMPERATURE_PROBLEM,
            RESTORING
        };
        State state;

        Lcd* lcd;
        ServoMotor* door;
        Led* greenLed;
        Led* redLed;

        TempSensor* tempSensor;

    public:
        TemperatureMonitoringTask(Lcd* lcd, ServoMotor* door, Led* greenLed, Led* redLed);
        void init(int period);
        void tick();
};

#endif