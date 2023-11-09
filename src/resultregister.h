#ifndef RESULTREGISTER_H
#define RESULTREGISTER_H

#define RESULT_REGISTER_SIZE 11

#include "register.h"
#include <QObject>

class ResultRegister : public Register {
    Q_OBJECT

public:
    ResultRegister();
    void clear();

signals:
    void valueChanged(QVector<int>*);
};

#endif // RESULTREGISTER_H
