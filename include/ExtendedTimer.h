//
// Created by szymon on 21/07/2021.
//

#ifndef CANSATDUINO_EXTENDEDTIMER_H
#define CANSATDUINO_EXTENDEDTIMER_H

#include <SAMDTimerInterrupt.h>
#include <SAMD_ISR_Timer.h>
#include <Callable.h>

void Inter(void* param){
    auto* callable = reinterpret_cast<Callable*>(param);
    callable->Call();
}

class ExtendedTimer {
    SAMD_ISRTimer& local_timer;
    int callbacks = 0;
    Callable* callables[16]{};
public:
    explicit ExtendedTimer(SAMD_ISRTimer& timer) : local_timer(timer){}
    void SetInterval(unsigned long time, Callable* callable){
        callables[callbacks++] = callable;
        local_timer.setInterval(time, Inter, callable);
    }

    void InLoop(){
        for (int i = 0; i < callbacks; ++i)
            callables[i]->InLoop();
    }

};

#endif //CANSATDUINO_EXTENDEDTIMER_H
