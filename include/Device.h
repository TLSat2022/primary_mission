//
// Created by szymon on 21/07/2021.
//

#ifndef CANSATDUINO_DEVICE_H
#define CANSATDUINO_DEVICE_H

#include <Arduino.h>

class Device {
protected:
    bool initialized = false;

public:
    Device() = default;

    virtual bool Initialize() = 0;
    virtual bool Measure() = 0;

    virtual char* GetPrettyString(char* buffer) const = 0;
    virtual String GetPrettyString() const { char buffer[64]; return String(GetPrettyString(buffer)); };
    virtual char* GetCsvString(char* buffer) const = 0;
    virtual String GetCsvString() const { char buffer[64]; return String(GetPrettyString(buffer)); };

    virtual String GetName() const = 0;

    bool IsInitialized() { return initialized; }

    virtual ~Device() = default;
};


#endif //CANSATDUINO_DEVICE_H
