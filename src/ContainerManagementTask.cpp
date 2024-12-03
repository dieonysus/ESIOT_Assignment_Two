#include "ContainerManagementTask.h"
#include <EnableInterrupt.h>
#include "MsgService.h"
#include "Arduino.h"
#include "string.h"
#include "shared.h"

#define PIR_PIN 2
#define OPEN_BUTTON_PIN 12
#define CLOSE_BUTTON_PIN 13
#define TRIG_PIN 4
#define ECHO_PIN 5
#define FILLING_PERCENTAGE_SEND_INTERVAL 500

ContainerManagementTask::ContainerManagementTask(Lcd* lcd, ServoMotor* door, Led* greenLed, Led* redLed) {
    this->lcd = lcd;
    this->door = door;
    this->greenLed = greenLed;
    this->redLed = redLed;
}

void ContainerManagementTask::init(int period) {
    Task::init(period);

    openButton = new Button(OPEN_BUTTON_PIN);
    closeButton = new Button(CLOSE_BUTTON_PIN);

    sonar = new Sonar(TRIG_PIN, ECHO_PIN); 
    sonar->initSonar();                 

    pinMode(PIR_PIN, INPUT_PULLUP);
    enableInterrupt(PIR_PIN, wakeUp, RISING);

    MsgService.init();

    timeBeforeSleep = 20000;
    lastActivityTime = 0;

    timeBeforeCloseDoor = 5000;
    timeDoorOpened = 0;

    lastDataSentTime = 0;

    containerVolume = 20;
    sonarDistanceFromContainer = 5;
    prevFillingPercantage = 0;

    state = IDLE;
    stateAfterWakeUp = IDLE;

    door->close();
}


void ContainerManagementTask::tick() {
    unsigned long currentTime = millis();
    if (temperatureIsTooHigh) {
        lastActivityTime = currentTime;
        return;
    }

    long distance = sonar->measureDistance();
    long fillingPercentage = (containerVolume + sonarDistanceFromContainer - distance) * 100 / containerVolume;
    if (currentTime - lastDataSentTime >= 500 && fillingPercentage >= prevFillingPercantage && fillingPercentage <= 100) {
        lastDataSentTime = currentTime;
        prevFillingPercantage = fillingPercentage;
        MsgService.sendVolume(fillingPercentage);
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
        else if (prevFillingPercantage >= 100) {
            lastActivityTime = currentTime;
            door->close();
            state = CONTAINER_FULL;
        }
        break;

    case PROCESSING_WASTE:
        door->close();
        lastActivityTime = currentTime;
        lcd->updateLine(0, "WASTE RECEIVED");
        lcd->updateLine(1, "");
        delay(5000);
        if (prevFillingPercantage >= 100) {
            state = CONTAINER_FULL;
        } 
        else {
            state = IDLE;
        } 
        break;

    case CONTAINER_FULL:
        lcd->updateLine(0, "CONTAINER FULL");
        lcd->updateLine(1, "");
        greenLed->switchOff();
        redLed->switchOn();
        if (MsgService.isMsgAvailable()) {
            Msg* msg = MsgService.receiveMsg();
            if (msg->getContent() == "empty"){
                delay(100);
                state = EMPTYING;
            }
        }
        if (currentTime - lastActivityTime > timeBeforeSleep) {
            stateAfterWakeUp = CONTAINER_FULL;
            state = SLEEPING;
        }
        break;

    case EMPTYING:
        door->openReverse();
        prevFillingPercantage = 0;
        MsgService.sendMsg("0%");
        delay(2000);
        door->close();
        lastActivityTime = currentTime;
        state = IDLE;
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
// FILLING_PERCENTAGE_SENT_INTERVAL
// going to idle after recieving waste arrow add to FSM
// delete messages
// add wire to tmp sensor