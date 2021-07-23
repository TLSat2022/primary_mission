//
// Created by szymon on 21/07/2021.
//

#ifndef CANSATDUINO_DEVICEGROUP_H
#define CANSATDUINO_DEVICEGROUP_H

#include <DC/Device.h>
#include <DC/Callable.h>
#include <initializer_list>

template<int N>
class DeviceGroup : public Callable {
    bool bExecute = false;
public:
    Device* devices[N]{};

    DeviceGroup(std::initializer_list<Device*> list){
        int i = 0;
        for (auto device: list) {
            if(i < N)
                devices[i++] = device;
        }
    }

    DeviceGroup() = default;

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
