#ifndef __DOORCONTROL__
#define __DOORCONTROL__

#include "Task.h"
#include "ServoMotor.h"
#include "Button.h"

class DoorControl: public Task{
  int doorPin;
  int openBtnPin;
  int closeBtnPin;
  int openDoorTime;
  int t1;
  int t2;
  Button* openBtn;
  ServoMotor* door;
  Button* closeBtn;
  enum {waiting, openToEnterWaste, wasteReceived} state;

  public:

  DoorControl(int doorPin, int openBtnPin, int closeBtnPin);
  void init();
  void tick();
};

#endif