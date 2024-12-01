#include "Arduino.h"
#include "ContainerManagementTask.h"
#include "TemperatureMonitoringTask.h"
#include "Scheduler.h"
#include "shared.h"

Lcd lcd(0x27, 16, 4);
ServoMotor door(9);
Led greenLed(7);
Led redLed(8);
// volatile bool highTemp;

ContainerManagementTask containerManagementTask(&lcd, &door, &greenLed, &redLed);
TemperatureMonitoringTask temperatureMonitoringTask(&lcd, &door, &greenLed, &redLed);

Scheduler scheduler;
volatile bool temperatureIsTooHigh;

void setup() {
  Serial.begin(9600);
  lcd.init();
  containerManagementTask.init(100);
  temperatureMonitoringTask.init(1000);
  scheduler.init(100);
  scheduler.addTask(&containerManagementTask);
  scheduler.addTask(&temperatureMonitoringTask);
  temperatureIsTooHigh = false;
}

void loop() {
  scheduler.schedule();
  delay(1000);
}