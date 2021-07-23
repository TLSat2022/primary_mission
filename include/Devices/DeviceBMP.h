//
// Created by szymon on 22/07/2021.
//

#ifndef CANSATDUINO_DEVICEBMP_H
#define CANSATDUINO_DEVICEBMP_H

#include <Arduino.h>
#include <DC/Device.h>
#include <CanSatKit/CanSatKit.h>

class DeviceBMP : public Device{
    CanSatKit::BMP280 device;
    double temperature, pressure;
public:
    bool Initialize() override;
    bool Measure() override;
    char * GetPrettyString(char *buffer) const override;
    char * GetCsvString(char *buffer) const override;

    String GetName() const override { return "BMP280"; }
};


#endif //CANSATDUINO_DEVICEBMP_H
