#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__
#include <Arduino.h>
#include "ServoTimer2.h"


class ServoMotor{
  public:
  ServoMotor(int pin);
  void open();
  void close();
  void openReverse();
  
  protected:
  void on();
  void off();
  int pin;
  ServoTimer2 motor;
};

#endif