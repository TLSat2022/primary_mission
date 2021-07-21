//
// Created by szymon on 21/07/2021.
//

#include "Devices/Magnetometer.h"

bool Magnetometer::Initialize() {
    initialized = device.init();
    if(initialized) device.enableDefault();
    return initialized;
}

bool Magnetometer::Measure() {
    device.read();
    return true;
}

char *Magnetometer::GetPrettyString(char *buffer) const {
    sprintf(buffer, "M: %6d %6d %6d",
            device.m.x, device.m.y, device.m.z);
    return buffer;
}

char *Magnetometer::GetCsvString(char *buffer) const {
    sprintf(buffer, "%d;%d;%d",
            device.m.x, device.m.y, device.m.z);
}