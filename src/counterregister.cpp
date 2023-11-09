#include "counterregister.h"

CounterRegister::CounterRegister() {
    values = new QVector<int>(COUNTER_REGISTER_SIZE);

    for (int i = 0; i < COUNTER_REGISTER_SIZE; i++) {
        (*values)[i] = 0;
    }
}

CounterRegister::~CounterRegister() {
    if (!values) {
        delete values;
    }
}

void CounterRegister::clear() {
    for (int i = 0; i < COUNTER_REGISTER_SIZE; i++) {
        (*values)[i] = 0;
    }

    emit valueChanged(values);
}
