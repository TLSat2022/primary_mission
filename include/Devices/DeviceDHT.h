//
// Created by szymon on 21/07/2021.
//

#ifndef CANSATDUINO_DEVICEDHT_H
#define CANSATDUINO_DEVICEDHT_H

#include <DC/Device.h>
#include <DHT.h>

class DeviceDHT : public Device{
    DHT device;
public:
    explicit DeviceDHT(uint8_t, uint8_t);

    bool Initialize() override;
    bool Measure() override;
    char * GetPrettyString(char *buffer) const override;
    char * GetCsvString(char *buffer) const override;

    String GetName() const override { return "DHT"; }

    float temperature{}, humidity{};
};


#endif //CANSATDUINO_DEVICEDHT_H
