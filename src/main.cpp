#include <Arduino.h>
#include "GoToSleepTask.h"
#include "Led.h"
#include <EnableInterrupt.h>

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

unsigned long timeBeforeSleep = 5000;
unsigned long lastActivityTime = millis();
unsigned long timeToEnterWaste = 10000;

int pirPin = 2;
int buttonPin = 8;

void wakeUp(){}

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT_PULLUP); // read about floating pin!
  enableInterrupt(pirPin, wakeUp, RISING);
  pinMode(buttonPin, INPUT);
}

void loop() {
  switch(currentState) {

    case IDLE:
      if (millis() - lastActivityTime > timeBeforeSleep) {
        goToSleepTask.tick();
        lastActivityTime = millis();
      } 
      else if (digitalRead(buttonPin) == HIGH) { //debounce
        Serial.print(" BUTTON ");
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
