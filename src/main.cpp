#include "Arduino.h"
#include "ContainerManagementTask.h"
#include "Scheduler.h"

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(100);
  Task* t0 = new ContainerManagementTask();
  t0->init(100); 
  sched.addTask(t0);
}

void loop() {
  sched.schedule();
}