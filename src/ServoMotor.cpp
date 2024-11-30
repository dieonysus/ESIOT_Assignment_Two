#include <Arduino.h>
#include "ServoMotor.h"

ServoMotor::ServoMotor(int pin){
  this->pin = pin;
}

void ServoMotor::on(){
 motor.attach(pin);
}

void ServoMotor::open(){
  on();
  motor.write(2350);
  delay(500);
  off();
}

void ServoMotor::close(){
  on();
  motor.write(1400);
  delay(500);
  off();
}

void ServoMotor::openReverse(){
 on();
 motor.write(550);
 delay(1000); 
 off();
}

void ServoMotor::off(){
  motor.detach();
}