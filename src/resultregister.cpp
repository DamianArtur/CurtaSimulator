#include "resultregister.h"

ResultRegister::ResultRegister() {
    values = new QVector<int>(RESULT_REGISTER_SIZE);

    for (int i = 0; i < RESULT_REGISTER_SIZE; i++) {
        (*values)[i] = 0;
    }
}

void ResultRegister::clear() {
    for (int i = 0; i < RESULT_REGISTER_SIZE; i++) {
        (*values)[i] = 0;
    }

    emit valueChanged(values);
}
