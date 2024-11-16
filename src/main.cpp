#include <Arduino.h>
#include "GoToSleepTask.h"
#include "DoorControl.h"
#include <EnableInterrupt.h>

#define ServoPin 9
#define OpenBtnPin 3
#define CloseBtnPin 4

enum State {
  AVAILABLE,
  WAITING_FOR_OPEN
};

State currentState = AVAILABLE;

unsigned long timeBeforeSleep = 5000;
unsigned long lastActivityTime = millis();

GoToSleepTask goToSleepTask;

DoorControl doorControl(ServoPin,OpenBtnPin,CloseBtnPin);

int pirPin = 2;


void wakeUp(){}

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT_PULLUP); // read about floating pin!
  enableInterrupt(pirPin, wakeUp, RISING);
  doorControl.init();
}

void loop() {
  Serial.print("a");
  delay(2000);
  switch(currentState) {
    case AVAILABLE:
    if (millis() - lastActivityTime > timeBeforeSleep) {
      goToSleepTask.tick();
      lastActivityTime = millis();
    }
  }

  doorControl.tick();
}


