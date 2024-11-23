#include "ContainerManagementTask.h"
#include <EnableInterrupt.h>
#include "MsgService.h"

ContainerManagementTask::ContainerManagementTask() {}

void ContainerManagementTask::init() {
    pirPin = 2;
    ledPin[0] = 7;
    ledPin[1] = 8;
    buttonPin[0] = 12;
    buttonPin[1] = 13;

    greenLed = new Led(ledPin[0]);
    redLed = new Led(ledPin[1]);
    openButton = new Button(buttonPin[0]);
    closeButton = new Button(buttonPin[1]);
    door = new ServoMotor(9);

    state = IDLE;
    pinMode(pirPin, INPUT_PULLUP);
    enableInterrupt(pirPin, wakeUp, RISING);

    timeBeforeSleep = 20000;
    lastActivityTime = millis();

    MsgService.init();
}


void ContainerManagementTask::tick() {
    switch (state) {

    case IDLE:
        greenLed->switchOn();
        //LCD: PRESS OPEN TO ENTER WASTE
        if (millis() - lastActivityTime > timeBeforeSleep) {
            state = SLEEPING;
        }
        if (openButton->isPressed()) {
            state = WAITING_FOR_WASTE;
        }
        break;

    case SLEEPING: 
        //LCD: SLEEP
        goToSleep();
        break;

    case WAITING_FOR_WASTE:
        //LCD: PRESS CLOSE WHEN DONE
        if (closeButton->isPressed()) { // or timeout
            //close door
            state = PROCESSING_WASTE;
        }
        //if container full -> close door, container full state
        break;

    case PROCESSING_WASTE:
        //LCD: WASTE RECIEVED
        //DELAY T2 (5000)
        //if container full -> container full state
        //else -> idle state 
        break;

    case CONTAINER_FULL:
        //LCD: CONTAINER FULL
        greenLed->switchOff();
        redLed->switchOn();
        break;
    }
}


void ContainerManagementTask::goToSleep() {
    Serial.print(" SLEEP");
    delay(1000);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();

    Serial.print(" WAKE UP ");
    sleep_disable();
    lastActivityTime = millis();
    state = IDLE;
}

void ContainerManagementTask::wakeUp(){
}

