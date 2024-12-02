#include "Arduino.h"
#include "ContainerManagementTask.h"
#include "TemperatureMonitoringTask.h"
#include "Scheduler.h"
#include "shared.h"

#define DOOR_PIN 9
#define GREEN_LED_PIN 7
#define RED_LED_PIN 8

Lcd lcd(0x27, 16, 4);
ServoMotor door(DOOR_PIN);
Led greenLed(GREEN_LED_PIN);
Led redLed(RED_LED_PIN);

Scheduler scheduler;
ContainerManagementTask containerManagementTask(&lcd, &door, &greenLed, &redLed);
TemperatureMonitoringTask temperatureMonitoringTask(&lcd, &door, &greenLed, &redLed);

volatile bool temperatureIsTooHigh;

void setup() {
  Serial.begin(9600);
  lcd.init();
  scheduler.init(100);
  containerManagementTask.init(100);
  temperatureMonitoringTask.init(100);
  scheduler.addTask(&containerManagementTask);
  //scheduler.addTask(&temperatureMonitoringTask);
  temperatureIsTooHigh = false;
}

void loop() {
  scheduler.schedule();
}