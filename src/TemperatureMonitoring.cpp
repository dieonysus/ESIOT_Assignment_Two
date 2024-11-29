#include "TemperatureMonitoringTask.h"

TemperatureMonitoringTask::TemperatureMonitoringTask() {}

void TemperatureMonitoringTask::init() {
    state = NORMAL_TEMPERATURE;
}

void TemperatureMonitoringTask::tick() {
    switch (state) {

    case NORMAL_TEMPERATURE:
        break;
    
    case TEMPERATURE_PROBLEM:
        break;
    
    case RESTORING:
        break;
    }
}