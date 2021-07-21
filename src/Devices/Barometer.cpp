//
// Created by szymon on 21/07/2021.
//

#include "Devices/Barometer.h"

bool Barometer::Initialize() {
    initialized = device.init();
    if(initialized) device.enableDefault();
    return initialized;
}

bool Barometer::Measure() {
    pressure = device.readPressureMillibars();
    return !isnan(pressure);
}

char *Barometer::GetPrettyString(char *buffer) const {
    sprintf(buffer, "Pressure: %s mBar", String(pressure).c_str());
    return buffer;
}

char *Barometer::GetCsvString(char *buffer) const {
    sprintf(buffer, "%s", String(pressure).c_str());
    return buffer;
}
