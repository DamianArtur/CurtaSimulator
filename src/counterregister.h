#ifndef COUNTERREGISTER_H
#define COUNTERREGISTER_H

#define COUNTER_REGISTER_SIZE 6

#include "register.h"
#include <QObject>

class CounterRegister : public Register {
    Q_OBJECT

public:
    CounterRegister();

    ~CounterRegister();

    void clear();

signals:
    void valueChanged(QVector<int>*);
};

#endif // COUNTERREGISTER_H
