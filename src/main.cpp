#include "ContainerManagementTask.h"

ContainerManagementTask containerManagementTask;

void setup() {
  Serial.begin(9600);
  containerManagementTask.init();

}

void loop() {
  containerManagementTask.tick();
}