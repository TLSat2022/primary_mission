//
// Created by szymon on 21/07/2021.
//

#ifndef CANSATDUINO_ACCGYRO_H
#define CANSATDUINO_ACCGYRO_H

#include <Device.h>
#include <LSM6.h>

class AccGyro : public Device{
    LSM6 device;
public:
    bool Initialize() override;
    bool Measure() override;
    char * GetPrettyString(char *buffer) const override;
    char * GetCsvString(char *buffer) const override;

    String GetName() const override { return "accelerometer and gyroscope"; }
};


#endif //CANSATDUINO_ACCGYRO_H
