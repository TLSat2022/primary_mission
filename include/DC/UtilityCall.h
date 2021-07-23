//
// Created by szymon on 21/07/2021.
//

#ifndef CANSATDUINO_UTILITYCALL_H
#define CANSATDUINO_UTILITYCALL_H

#include <Arduino.h>
#include <DC/Callable.h>

class UtilityCall : public Callable {
    using Callback = void(*)();
    bool bExecute = false;
    Callback callback{};

public:
    explicit UtilityCall(Callback callback) : callback(callback) {}

    void Call() override {
        bExecute = true;
    }

    void InLoop() override {
        if(bExecute) callback();
        bExecute = false;
    }
};

#endif //CANSATDUINO_UTILITYCALL_H
