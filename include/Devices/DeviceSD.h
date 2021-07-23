//
// Created by szymon on 22/07/2021.
//

#ifndef CANSATDUINO_DEVICESD_H
#define CANSATDUINO_DEVICESD_H

#include <SD.h>
#include <DC/Device.h>

class DeviceSD : public Device{
    uint8_t CS = 0;
public:

    explicit DeviceSD(uint8_t pin = 11) : CS(pin){}

    bool Initialize() override;
    bool Measure() override;
    char * GetPrettyString(char *buffer) const override;
    char * GetCsvString(char *buffer) const override;

    String GetName() const override { return "SD"; }
};


#endif //CANSATDUINO_DEVICESD_H
