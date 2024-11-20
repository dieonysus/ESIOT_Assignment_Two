#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__
#include <Servo.h>

class ServoMotor{
  public:
  ServoMotor(int pin);
  void on();
  void openDoor();
  void closeDoor();
  void openDoorReverse();
  void off();
  
  protected:
  int pin;
  Servo motor;
};

#endif