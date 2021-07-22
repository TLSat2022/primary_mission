//
// Created by szymon on 22/07/2021.
//

#include "Devices/DeviceSD.h"



bool DeviceSD::Initialize() {
    initialized = SD.begin(CS);
    return initialized;
}

bool DeviceSD::Measure() {
    return initialized;
}

char *DeviceSD::GetPrettyString(char *buffer) const {
    return nullptr;
}

char *DeviceSD::GetCsvString(char *buffer) const {
    return nullptr;
}
