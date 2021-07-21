//
// Created by szymon on 21/07/2021.
//

#ifndef CANSATDUINO_DEVICEGROUP_H
#define CANSATDUINO_DEVICEGROUP_H

#include <Device.h>
#include <Callable.h>

template<int N>
class DeviceGroup : public Callable {
    bool bExecute = false;
public:
    Device* devices[N]{};

    void Call() override{
        bExecute = true;
    }

    Device*& operator[](size_t index){
        if(index < N){
            return devices[index];
        }else{
            return devices[0];
        }
    }

    void InLoop() override{
        if(bExecute)
            for (auto & device : devices)
                device->Measure();
        bExecute = false;
    }

};


#endif //CANSATDUINO_DEVICEGROUP_H
