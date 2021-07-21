//
// Created by szymon on 21/07/2021.
//

#include "Devices/AccGyro.h"

bool AccGyro::Initialize() {
    initialized = device.init();
    if(initialized) device.enableDefault();
    return initialized;
}

bool AccGyro::Measure() {
    device.read();
    return true;
}

char *AccGyro::GetPrettyString(char *buffer) const {
    sprintf(buffer, "A: %6d %6d %6d    G: %6d %6d %6d   ",
            device.a.x, device.a.y, device.a.z,
            device.g.x, device.g.y, device.g.z);
    return buffer;
}

char *AccGyro::GetCsvString(char *buffer) const {
    sprintf(buffer, "%d;%d;%d;%d;%d;%d;",
            device.a.x, device.a.y, device.a.z,
            device.g.x, device.g.y, device.g.z);
}
