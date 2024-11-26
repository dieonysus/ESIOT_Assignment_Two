#include "ServoMotor.h"
#include "Arduino.h"

ServoMotor::ServoMotor(int pin){
  this->pin = pin;
}

void ServoMotor::on(){
 motor.attach(pin);
}

void ServoMotor::open(){
  on();
  motor.write(2250);
  delay(500);
  off();
}

void ServoMotor::close(){
  on();
  motor.write(1500);
  delay(500);
  off();
}

void ServoMotor::openReverse(){
 on();
 motor.write(750);
 delay(500); 
 off();
}

void ServoMotor::off(){
  motor.detach();
}