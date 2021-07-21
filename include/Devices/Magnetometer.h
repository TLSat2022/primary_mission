//
// Created by szymon on 21/07/2021.
//

#ifndef CANSATDUINO_MAGNETOMETER_H
#define CANSATDUINO_MAGNETOMETER_H

#include <Device.h>
#include <LIS3MDL.h>

class Magnetometer : public Device{
    LIS3MDL device;
public:
    bool Initialize() override;
    bool Measure() override;
    char * GetPrettyString(char *buffer) const override;
    char * GetCsvString(char *buffer) const override;

    String GetName() const override { return "Magnetometer"; }
};


#endif //CANSATDUINO_MAGNETOMETER_H
