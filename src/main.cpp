#include "Arduino.h"
#include "ContainerManagementTask.h"
#include "TemperatureMonitoringTask.h"
#include "Scheduler.h"

Lcd lcd(0x27, 16, 4);
ServoMotor door(9);
Led greenLed(7);
Led redLed(8);
volatile bool temperatureIsTooHigh = false;

ContainerManagementTask containerManagementTask(&lcd, &door, &greenLed, &redLed, &temperatureIsTooHigh);
TemperatureMonitoringTask temperatureMonitoringTask(&lcd, &door, &greenLed, &redLed);
Scheduler scheduler;

void setup() {
  Serial.begin(9600);
  lcd.init();

  containerManagementTask.init(100);
  temperatureMonitoringTask.init(1000);
  scheduler.init(100);
  scheduler.addTask(&containerManagementTask);
  //scheduler.addTask(&temperatureMonitoringTask);
}

void loop() {
  // temperatureIsTooHigh = !temperatureIsTooHigh;
    if (temperatureIsTooHigh) {
        Serial.print(" true ");
    } else {
        Serial.print(" false ");
    }
  scheduler.schedule();
  delay(1000);
}