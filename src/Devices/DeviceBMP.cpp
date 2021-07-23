//
// Created by szymon on 22/07/2021.
//

#include "Devices/DeviceBMP.h"

bool DeviceBMP::Initialize() {
    initialized = device.begin();
    if(initialized) device.setOversampling(16);

    return initialized;
}

bool DeviceBMP::Measure() {
    device.measureTemperatureAndPressure(temperature, pressure);
    return !(isnan(temperature) | isnan(pressure));
}

char *DeviceBMP::GetPrettyString(char *buffer) const {
    sprintf(buffer, "Temperature: %s C, Pressure: %s mBar", String(temperature).c_str(), String(pressure).c_str());
    return buffer;
}

char *DeviceBMP::GetCsvString(char *buffer) const {
    sprintf(buffer, "%s;%s;", String(temperature).c_str(), String(pressure).c_str());
    return buffer;
}
