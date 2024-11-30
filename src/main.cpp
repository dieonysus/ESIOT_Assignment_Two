#include "Arduino.h"
#include "ContainerManagementTask.h"
#include "Scheduler.h"
#include "ReadTempTask.h"

Lcd lcd(0x27, 16, 4);
ServoMotor door(9);
Led greenLed(7);
Led redLed(8);

ContainerManagementTask containerManagementTask(&lcd, &door, &greenLed, &redLed);
Scheduler sched;
ReadTempTask readTempTask;

void setup() {
  Serial.begin(9600);
  lcd.init();
  readTempTask.init();
  
  containerManagementTask.init(100);
  sched.init(100);
  sched.addTask(containerManagementTask);
}

void loop() {
  sched.schedule();
}