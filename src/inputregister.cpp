#include "inputregister.h"

InputRegister::InputRegister() {
    values = new QVector<int>(INPUT_REGISTER_SIZE);
    for(int i = 0; i < INPUT_REGISTER_SIZE; i++) {
        (*values)[i] = 0;
    }
}

void InputRegister::setValue(const int number, const int newValue) {
    (*values)[number] = newValue;
    emit valueChanged(number, newValue);
}

QVector<int>* InputRegister::getValues() const {
    return values;
}

int InputRegister::getValue(int number) const {
    return (*values)[number];
}
