#ifndef __CONTAINERMANAGEMENTTASK__
#define __CONTAINERMANAGEMENTTASK__

#include "Task.h"
#include <Arduino.h>
#include <avr/sleep.h>
#include "Led.h"
#include "Button.h"
#include "ServoMotor.h"
#include "Lcd.h"
#include "Sonar.h"

class ContainerManagementTask: public Task {

    private:
        Lcd* lcd;
        ServoMotor* door;
        Led* greenLed;
        Led* redLed;

        Button* openButton;
        Button* closeButton;
        Sonar* sonar;

        unsigned long timeBeforeSleep;
        unsigned long lastActivityTime;
        unsigned long timeDoorOpened;
        unsigned long timeBeforeCloseDoor;     
        unsigned long lastDataSentTime; 
        long containerVolume;
        long sonarDistanceFromContainer;  
        long prevFillingPercantage;

        enum State {
            IDLE,
            SLEEPING,
            WAITING_FOR_WASTE,
            PROCESSING_WASTE,
            CONTAINER_FULL,
            EMPTYING
        };
        State state;
        State stateAfterWakeUp;


    public:
        ContainerManagementTask(Lcd* lcd, ServoMotor* door, Led* greenLed, Led* redLed);
        void init(int period);
        void tick();

    private:
        void goToSleep();
        static void wakeUp();
};

#endif