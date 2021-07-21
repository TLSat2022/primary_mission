//
// Created by szymon on 21/07/2021.
//

#ifndef CANSATDUINO_CALLABLE_H
#define CANSATDUINO_CALLABLE_H


class Callable {
public:
    virtual void Call() = 0;
    virtual void InLoop() = 0;
};

#endif //CANSATDUINO_CALLABLE_H
