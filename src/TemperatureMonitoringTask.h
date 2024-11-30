#ifndef __TEMPERATUREMONITORINGTASK__
#define __TEMPERATUREMONITORINGTASK__

#include "Task.h"

class TemperatureMonitoringTask : public Task {

    private:
        enum State {
            NORMAL_TEMPERATURE,
            TEMPERATURE_PROBLEM,
            RESTORING
        };
        State state;

    public:
        TemperatureMonitoringTask();
        void init();
        void tick();
};

#endif