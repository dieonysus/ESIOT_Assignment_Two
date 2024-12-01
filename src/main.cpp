#include "Arduino.h"
#include "ContainerManagementTask.h"
#include "TemperatureMonitoringTask.h"
#include "Scheduler.h"

Lcd lcd(0x27, 16, 4);
ServoMotor door(9);
Led greenLed(7);
Led redLed(8);

ContainerManagementTask containerManagementTask(&lcd, &door, &greenLed, &redLed);
TemperatureMonitoringTask temperatureMonitoringTask(&lcd, &door, &greenLed, &redLed);
Scheduler scheduler;

void setup() {
  Serial.begin(9600);
  lcd.init();

  containerManagementTask.init(100);
  temperatureMonitoringTask.init(1000);
  scheduler.init(100);
  scheduler.addTask(&containerManagementTask);
  scheduler.addTask(&temperatureMonitoringTask);
}

void loop() {
  scheduler.schedule();
}