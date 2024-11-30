#include <Arduino.h>
#include "ContainerManagementTask.h"

Lcd lcd(0x27, 16, 4);
ServoMotor door(9);
Led greenLed(7);
Led redLed(8);

ContainerManagementTask containerManagementTask(&lcd, &door, &greenLed, &redLed);



void setup() {
  Serial.begin(9600);
  lcd.init();
  containerManagementTask.init();
}

void loop() {
  containerManagementTask.tick();
}