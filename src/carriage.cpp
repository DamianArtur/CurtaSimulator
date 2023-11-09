#include "carriage.h"

Carriage::Carriage() {
    currentPosition = 1;
}

int Carriage::getPosition() const {
    return currentPosition;
}

void Carriage::setPosition(const int newPosition) {
    currentPosition = newPosition;
    emit valueChanged(currentPosition);
}

void Carriage::operator++(int) {
    if (currentPosition < MAX_CARRIAGE_POISTION) {
        currentPosition++;
    }
    emit valueChanged(currentPosition);
}

void Carriage::operator--(int) {
    if (currentPosition > MIN_CARRIAGE_POSITION) {
        currentPosition--;
    }
    emit valueChanged(currentPosition);
}
