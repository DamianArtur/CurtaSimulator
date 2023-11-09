#include "counterswitch.h"

CounterSwitch::CounterSwitch() {
    currentPosition = ADDITION;
}

int CounterSwitch::getValue() const {
    return currentPosition;
}

void CounterSwitch::setValue(const int newValue) {
    currentPosition = newValue;
    emit valueChanged(newValue);
}
