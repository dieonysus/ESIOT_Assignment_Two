#include "ServoMotor.h"
#include "Arduino.h"

ServoMotor::ServoMotor(int pin){
  this->pin = pin;
}

void ServoMotor::on(){
 motor.attach(pin);
}

void ServoMotor::openDoor(){
  motor.write(180);
  delay(300);
}

void ServoMotor::closeDoor(){
  motor.write(90);
  delay(300);
}

void ServoMotor::openDoorReverse(){
 motor.write(0);
 delay(300); 
}

void ServoMotor::off(){
  motor.detach();
}