#include <Arduino.h>
#include "GoToSleepTask.h"
#include "Led.h"
#include <EnableInterrupt.h>
#include "DoorControl.h"
#include "ServoMotor.h"
#include <EnableInterrupt.h>
#include "DoorControl.h"
#include "ServoMotor.h"
#include <EnableInterrupt.h>

<<<<<<< HEAD
=======
Led ledRED(4);  
Led ledGREEN(7);
ServoMotor myServo(9);

// #define ServoPin 9
// #define OpenBtnPin 8
#define CloseBtnPin 10
#define buttonPin 8

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

State currentState = IDLE;
Led ledRed(4);  
Led ledGreen(7);
GoToSleepTask goToSleepTask;
Led ledRed(4);  
Led ledGreen(7);
GoToSleepTask goToSleepTask;

unsigned long timeBeforeSleep = 5000;
unsigned long lastActivityTime = millis();
unsigned long timeToEnterWaste = 10000;

<<<<<<< HEAD
=======

GoToSleepTask goToSleepTask;

// DoorControl doorControl(ServoPin,buttonPin,CloseBtnPin);

int pirPin = 2;


void wakeUp(){}

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT_PULLUP); // read about floating pin!
  enableInterrupt(pirPin, wakeUp, RISING);
  pinMode(buttonPin, INPUT);
  // doorControl.init();
  // doorControl.init();
}

void loop() {
    switch (currentState) {
    switch (currentState) {

    case IDLE:
      if (millis() - lastActivityTime > timeBeforeSleep) {
        goToSleepTask.tick();
        lastActivityTime = millis();
      } 
      else if (digitalRead(buttonPin) == HIGH) { //debounce
        Serial.print(" BUTTON ");
        // doorControl.tick();
        myServo.on();
        myServo.openDoor();
        myServo.off();
        // doorControl.tick();
        myServo.on();
        myServo.openDoor();
        myServo.off();
        currentState = WAITING_FOR_WASTE;
        lastActivityTime = millis();
      }
      break;

    case WAITING_FOR_WASTE:
    // open door
      Serial.print(" PRESS CLOSE WHEN DONE ");
      delay(500);
      if (millis() - lastActivityTime > timeToEnterWaste) {
        Serial.print(" TIMEOUT ");
        myServo.on();
        myServo.closeDoor();
        myServo.off();
        myServo.on();
        myServo.closeDoor();
        myServo.off();
        delay(1000);
        currentState = IDLE;
        lastActivityTime = millis();
      }
      else if (digitalRead(buttonPin) == HIGH) { //debounce 
        Serial.print(" CLOSING THE DOOR ");
        delay(1000);
        currentState = IDLE;
        lastActivityTime = millis();
      }
      // if is full
      break;

    case PROCESSING_WASTE:
      //close door
      Serial.print("WASTE RECIEVED");
      // if is full
    break;
    case CONTAINER_FULL:
      // red led
    break;
  }
   
}
  

 



