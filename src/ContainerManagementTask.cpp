#include "ContainerManagementTask.h"
#include <EnableInterrupt.h>
#include "MsgService.h"
#include "Arduino.h"
#include "string.h"


ContainerManagementTask::ContainerManagementTask() {}

void ContainerManagementTask::init() {
    pirPin = 2;
    ledPin[0] = 7;
    ledPin[1] = 8;
    buttonPin[0] = 12;
    buttonPin[1] = 13;
    servoPin = 9;
    trigPin = 4; 
    echoPin = 5;

    greenLed = new Led(ledPin[0]);
    redLed = new Led(ledPin[1]);
    openButton = new Button(buttonPin[0]);
    closeButton = new Button(buttonPin[1]);
    door = new ServoMotor(servoPin);
    sonar = new Sonar(trigPin, echoPin); 
    sonar->initSonar();                 

    pinMode(pirPin, INPUT_PULLUP);
    enableInterrupt(pirPin, wakeUp, RISING);
    door->close();

    MsgService.init();

    lcd = new Lcd(0x27, 16, 4);
    lcd->init();
    timeBeforeSleep = 10000;
    lastActivityTime = 0;
    timeBeforeCloseDoor = 10000;
    timeDoorOpened = 0;
    lastDataSentTime = 0;
    state = IDLE;

    containerVolume = 20;
    sonarDistanceFromContainer = 5;
    prevFillingPercantage = 0;
    stateAfterWakeUp = IDLE;
}


void ContainerManagementTask::tick() {
    unsigned long currentTime = millis();
    long distance = sonar->measureDistance();
    long fillingPercentage = (containerVolume + sonarDistanceFromContainer - distance) * 100 / containerVolume;
    if (currentTime - lastDataSentTime >= 1000 && fillingPercentage > prevFillingPercantage && fillingPercentage <= 100) {
        MsgService.sendVolume(fillingPercentage);
        lastDataSentTime = currentTime;
        prevFillingPercantage = fillingPercentage;
    }

    switch(state) {

    case IDLE:
        greenLed->switchOn();
        redLed->switchOff();
        lcd->updateLine(0, "PRESS OPEN TO");
        lcd->updateLine(1, "ENTER WASTE");
        if (currentTime - lastActivityTime > timeBeforeSleep) {
            stateAfterWakeUp = IDLE;
            state = SLEEPING;
        }
        else if (openButton->isPressed()) {
            state = WAITING_FOR_WASTE;
            timeDoorOpened = currentTime;
            door->open();
        }
        break;

    case SLEEPING: 
        lcd->updateLine(0, "SLEEP");
        lcd->updateLine(1, "");
        goToSleep();
        break;

    case WAITING_FOR_WASTE:
        lcd->updateLine(0, "PRESS CLOSE");
        lcd->updateLine(1, "WHEN DONE");
        if (closeButton->isPressed() || (currentTime - timeDoorOpened) >= timeBeforeCloseDoor) {
            state = PROCESSING_WASTE;
        }
        else if (fillingPercentage >= 100) {
            state = CONTAINER_FULL;
        }
        break;

    case PROCESSING_WASTE:
        door->close();
        lastActivityTime = currentTime;
        lcd->updateLine(0, "WASTE RECEIVED");
        lcd->updateLine(1, "");
        delay(5000);
        if (fillingPercentage >= 100) { 
            state = CONTAINER_FULL;
        } 
        else {
            state = IDLE;
        } 
        break;

    case CONTAINER_FULL:
        door->close();
        lcd->updateLine(0, "CONTAINER FULL");
        lcd->updateLine(1, "");
        greenLed->switchOff();
        redLed->switchOn();
        if (currentTime - lastActivityTime > timeBeforeSleep) {
            stateAfterWakeUp = CONTAINER_FULL;
            state = SLEEPING;
        }
        break;
    }
}


void ContainerManagementTask::goToSleep() {
    delay(1000);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();

    sleep_disable();
    lastActivityTime = millis();
    state = stateAfterWakeUp;
}

void ContainerManagementTask::wakeUp(){
}

// TODO: doesnt become full from processing_waste state
// reverse open after during emptying + close back

