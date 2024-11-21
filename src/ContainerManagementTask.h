#ifndef __CONTAINERMANAGEMENTTASK__
#define __CONTAINERMANAGEMENTTASK__

#include "Task.h"
#include <Arduino.h>
#include <avr/sleep.h>
#include "Led.h"
#include "Button.h"

class ContainerManagementTask: public Task {

    private:
        int pirPin;
        int ledPin[2];
        int buttonPin[2];
        Led* greenLed;
        Led* redLed;
        Button* openButton;
        Button* closeButton;
        
        unsigned long timeBeforeSleep;
        unsigned long lastActivityTime;

        enum State {
            IDLE,
            SLEEPING,
            WAITING_FOR_WASTE,
            PROCESSING_WASTE,
            CONTAINER_FULL,
            EMPTYING_PROCESS,
            RESTORE,
            TEMPERATURE_PROBLEM
        };
        State state;


    public:
        ContainerManagementTask();
        void init();
        void tick();

    private:
        void goToSleep();
        static void wakeUp();
};

#endif