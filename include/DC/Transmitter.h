//
// Created by szymon on 22/07/2021.
//

#ifndef CANSATDUINO_TRANSMITTER_H
#define CANSATDUINO_TRANSMITTER_H

#include <DC/Device.h>

class Transmitter : public Device{

public:
    explicit Transmitter() {

    }

    bool Initialize() override;
    bool Measure() override;
    char * GetPrettyString(char *buffer) const override;
    char * GetCsvString(char *buffer) const override;

    void Transmit(float number);

    String GetName() const override { return "Transmitter"; }
};


#endif //CANSATDUINO_TRANSMITTER_H
