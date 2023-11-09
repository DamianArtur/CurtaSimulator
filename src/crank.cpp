#include "crank.h"

Crank::Crank() {
    currentPosition = true;
}

void Crank::setPosition(const bool newPosition) {
    currentPosition = newPosition;
    emit valueChanged(currentPosition);
}

bool Crank::getPosition() const {
    return currentPosition;
}

void Crank::turn(bool crankPosition, int switchPosition, int carriage, QVector<int>* counterRegisterValues) {
    if (crankPosition) {
        if(switchPosition == 0) {
            (*counterRegisterValues)[carriage-1]++;
        } else {
            (*counterRegisterValues)[carriage-1]--;
        }
    } else {
        if(switchPosition == 0) {
            (*counterRegisterValues)[carriage-1]--;
        } else {
            (*counterRegisterValues)[carriage-1]++;
        }
    }

    bool overflow = false;
    bool underflow = false;

    for (int i = 0; i < COUNTER_REGISTER_SIZE; i++) {
        if (overflow) {
            (*counterRegisterValues)[i]++;
            overflow = false;
        }
        if (underflow) {
            (*counterRegisterValues)[i]--;
            underflow = false;
        }

        if ((*counterRegisterValues)[i] > MAX_DIGIT) {
            (*counterRegisterValues)[i] -= 10;
            overflow = true;
        }
        if ((*counterRegisterValues)[i] < MIN_DIGIT) {
            (*counterRegisterValues)[i] += 10;
            underflow = true;
        }
    }

    emit counterRegisterChanged(counterRegisterValues);
}

void Crank::turn(bool crankPosition, int carriage, QVector<int>* inputRegisterValues, QVector<int>* resultRegisterValues) {
    if (crankPosition) {
        for(int i = 0; i < INPUT_REGISTER_SIZE; i++) {
            if (carriage-1+i < RESULT_REGISTER_SIZE)
            (*resultRegisterValues)[carriage-1+i] += (*inputRegisterValues)[i];
        }
    } else {
        for(int i = 0; i < INPUT_REGISTER_SIZE; i++) {
            if (carriage-1+i < RESULT_REGISTER_SIZE)
            (*resultRegisterValues)[carriage-1+i] -= (*inputRegisterValues)[i];
        }
    }

    bool overflow = false;
    bool underflow = false;

    for (int i = 0; i < RESULT_REGISTER_SIZE; i++) {
        if (overflow) {
            (*resultRegisterValues)[i]++;
            overflow = false;
        }
        if (underflow) {
            (*resultRegisterValues)[i]--;
            underflow = false;
        }

        if ((*resultRegisterValues)[i] > MAX_DIGIT) {
            (*resultRegisterValues)[i] -= 10;
            overflow = true;
        }
        if ((*resultRegisterValues)[i] < MIN_DIGIT) {
            (*resultRegisterValues)[i] += 10;
            underflow = true;
        }
    }

    emit resultRegisterChanged(resultRegisterValues);
}
