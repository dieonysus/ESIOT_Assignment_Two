#include "ContainerManagementTask.h"
#include <EnableInterrupt.h>

ContainerManagementTask::ContainerManagementTask() {}

void ContainerManagementTask::init() {
    pirPin = 2;
    ledPin[0] = 7;
    ledPin[1] = 8;
    buttonPin[0] = 12;
    buttonPin[1] = 13;
    servoPin = 9;

    greenLed = new Led(ledPin[0]);
    redLed = new Led(ledPin[1]);
    openButton = new Button(buttonPin[0]);
    closeButton = new Button(buttonPin[1]);
    door = new ServoMotor(servoPin);

    pinMode(pirPin, INPUT_PULLUP);
    enableInterrupt(12, wakeUp, RISING);
    door->close();

    timeBeforeSleep = 10000;
    lastActivityTime = 0;
    timeBeforeCloseDoor = 2000;
    openDoorTime = 0;
    state = IDLE;
}


void ContainerManagementTask::tick() {
    unsigned long currentTime = millis();

    switch(state) {

    case IDLE:
        greenLed->switchOn();
        //LCD: PRESS OPEN TO ENTER WASTE
        if ((currentTime - lastActivityTime)  > timeBeforeSleep) {
            state = SLEEPING;
        }
        if (openButton->isPressed()) {
            door->open();
            openDoorTime = currentTime;
            state = WAITING_FOR_WASTE;
        }
        break;

    case SLEEPING: 
        //LCD: SLEEP
        goToSleep();
        break;

    case WAITING_FOR_WASTE:
        //LCD: PRESS CLOSE WHEN DONE
        if (closeButton->isPressed() || (currentTime - openDoorTime) >= timeBeforeCloseDoor) {
            door->close();
            state = PROCESSING_WASTE;
            lastActivityTime = currentTime;
        }
        //if full -> close door, container full state
        break;

    case PROCESSING_WASTE:
        //LCD: WASTE RECIEVED
        //DELAY T2
        //if full -> container full state
        //else -> idle state 
        delay(100);
        state = IDLE;
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

