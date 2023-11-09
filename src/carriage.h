#ifndef CARRIAGE_H
#define CARRIAGE_H

#define MAX_CARRIAGE_POISTION 6
#define MIN_CARRIAGE_POSITION 1

#include <QObject>

class Carriage : public QObject {
    Q_OBJECT

public:
    Carriage();

    int getPosition() const;

    void setPosition(const int);

    void operator++(int); // turn left
    void operator--(int); // turn right

signals:
    void valueChanged(int newPosition);

private:
    int currentPosition;
};

#endif // CARRIAGE_H
