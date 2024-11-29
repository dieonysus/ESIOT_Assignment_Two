#include <Arduino.h>
#include "ContainerManagementTask.h"
#include "ReadTempTask.h"

ContainerManagementTask containerManagementTask;
ReadTempTask readTempTask;

void setup() {
  Serial.begin(9600);
  containerManagementTask.init();
  readTempTask.init();

}

void loop() {
  containerManagementTask.tick();
}