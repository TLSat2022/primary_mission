//
// Created by szymon on 22/07/2021.
//

#include "DC/Transmitter.h"

bool Transmitter::Initialize() {

    return true;
}

bool Transmitter::Measure() {
    return true;
}

char *Transmitter::GetPrettyString(char *buffer) const {
    return nullptr;
}

char *Transmitter::GetCsvString(char *buffer) const {
    return nullptr;
}

void Transmitter::Transmit(float number) {


}
