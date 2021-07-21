//
// Created by szymon on 21/07/2021.
//

#ifndef CANSATDUINO_BAROMETER_H
#define CANSATDUINO_BAROMETER_H

#include <Device.h>
#include <LPS.h>

class Barometer : public Device{
    LPS device;
public:
    bool Initialize() override;
    bool Measure() override;
    char * GetPrettyString(char *buffer) const override;
    char * GetCsvString(char *buffer) const override;

    String GetName() const override { return "Barometer"; }

    float pressure;
};


#endif //CANSATDUINO_BAROMETER_H
