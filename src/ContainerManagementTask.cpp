#include "ContainerManagementTask.h"
#include <EnableInterrupt.h>
#include "MsgService.h"
#include "Arduino.h"

ContainerManagementTask::ContainerManagementTask() {}

void ContainerManagementTask::init(int period) {
    Task::init(period);
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
    enableInterrupt(12, wakeUp, RISING);
    door->close();

    MsgService.init();

    lcd = new Lcd(0x27, 16, 4);
    lcd->init();
    timeBeforeSleep = 20000;
    lastActivityTime = 0;
    timeBeforeCloseDoor = 10000;
    openDoorTime = 0;
    state = IDLE;
}


void ContainerManagementTask::tick() {
    unsigned long currentTime = millis();
    long distance = sonar->measureDistance();

    switch(state) {

    case IDLE:
        greenLed->switchOn();
        // LCD: PRESS OPEN TO ENTER WASTE
        if ((currentTime - lastActivityTime) > timeBeforeSleep) {
            state = SLEEPING;
        }
        if (openButton->isPressed()) {
            door->open();
            Serial.println("Open");
            openDoorTime = currentTime;
            state = WAITING_FOR_WASTE;
        }
        break;

    case SLEEPING:
        // LCD: SLEEP
        goToSleep();
        break;

    case WAITING_FOR_WASTE:
        lcd->updateLine(0, "PRESS CLOSE");
        lcd->updateLine(1, "WHEN DONE");
        if (closeButton->isPressed() || (currentTime - openDoorTime) >= timeBeforeCloseDoor) {
            door->close();
            Serial.println("Close");
            state = PROCESSING_WASTE;
            lastActivityTime = currentTime;
        }

        else if (distance < 2)
        {
            door->close();
            state = CONTAINER_FULL;
        }

        break;

    case PROCESSING_WASTE:
        lcd->updateLine(0, "WASTE RECEIVED");
        lcd->updateLine(1, "");
        
        
        if (distance < 2) { 
            state = CONTAINER_FULL;
        } 
        
        else {
            state = IDLE;
        }
        //close door
        //DELAY T2 (5000)
        //if container full -> container full state
        //else -> idle state 
        delay(100);
        state = IDLE;
        break;

    case CONTAINER_FULL:
        //LCD: CONTAINER FULL
        // greenLed->switchOff();
        // redLed->switchOn();
        
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
