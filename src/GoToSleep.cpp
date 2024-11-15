#include "GoToSleepTask.h"
#include <Arduino.h>
#include <avr/sleep.h>

GoToSleepTask::GoToSleepTask() {
}

void GoToSleepTask::init() {
}

void GoToSleepTask::tick() {
    Serial.print(" SLEEP");
    delay(1000);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();

    Serial.print(" WAKE UP ");
    sleep_disable();
}