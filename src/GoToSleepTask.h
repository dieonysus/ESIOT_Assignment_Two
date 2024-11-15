#ifndef __GOTOSLEEPTASK__
#define __GOTOSLEEPTASK__

#include "Task.h"

class GoToSleepTask: public Task{
    public:
        GoToSleepTask();
        void init();
        void tick();
};

#endif