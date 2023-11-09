#ifndef REGISTER_H
#define REGISTER_H

#include <QObject>

class Register : public QObject {
    Q_OBJECT

public:
    virtual QVector<int>* getValues();

protected:
    QVector<int>* values;
};

#endif // COUNTERREGISTER_H
