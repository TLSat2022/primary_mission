//
// Created by szymon on 21/07/2021.
//

#include "Devices/DeviceDHT.h"

bool DeviceDHT::Initialize() {
    device.begin();
    initialized = true;
    return true;
}

bool DeviceDHT::Measure() {
    temperature = device.readTemperature();
    humidity = device.readHumidity();
    return !(isnan(temperature) | isnan(humidity));
}

char *DeviceDHT::GetPrettyString(char *buffer) const {
    sprintf(buffer, "Temperature: %s, Humidity: %s",
            String(temperature).c_str(), String(humidity).c_str());
    return buffer;
}

char *DeviceDHT::GetCsvString(char *buffer) const {
    sprintf(buffer, "%s;%s;",
            String(temperature).c_str(), String(humidity).c_str());
    return buffer;
}

DeviceDHT::DeviceDHT(uint8_t pin, uint8_t type) : device(pin, type),
        temperature(0.0f),
        humidity(0.0f)
        {}
