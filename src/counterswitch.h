#ifndef COUNTERSWITCH_H
#define COUNTERSWITCH_H

#define ADDITION 0
#define SUBTRACTION 1

#include <QObject>

class CounterSwitch : public QObject {
    Q_OBJECT

public:
    CounterSwitch();

    int getValue() const;

    void setValue(const int);

signals:
    void valueChanged(int);

private:
    int currentPosition;
};

#endif // COUNTERSWITCH_H
