#include "DoorControl.h"
#include "Arduino.h"


DoorControl::DoorControl(int doorPin, int openBtnPin, int closeBtnPin){
  this->doorPin = doorPin;
  this->openBtnPin = openBtnPin;
  this->closeBtnPin = closeBtnPin;
}

void DoorControl::init(){
  door = new ServoMotor(doorPin);
  openBtn = new Button(openBtnPin);
  closeBtn = new Button(closeBtnPin);
  door->on();
  door->closeDoor();
  door->off();
  t1 = 2000;
  openDoorTime = 0;
  state = waiting;
}

void DoorControl::tick(){
  switch(state){
   case waiting:
    if(openBtn->isPressed()){
     door->on();
     door->openDoor();
     door->off();
     openDoorTime = millis();
     state = openToEnterWaste;
   }
   break;
   case openToEnterWaste:
    int passedTime = millis() - openDoorTime;
    if(passedTime >= t1 || closeBtn->isPressed()){
     door->on();
     door->closeDoor();
     door->off();
     state = wasteReceived;
     delay(1);
     state = waiting;
   }
   break;
  }
}
