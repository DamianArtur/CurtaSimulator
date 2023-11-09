#ifndef CRANK_H
#define CRANK_H

#define COUNTER_REGISTER_SIZE 6
#define INPUT_REGISTER_SIZE 8
#define RESULT_REGISTER_SIZE 11
#define MAX_DIGIT 9
#define MIN_DIGIT 0

#include <QObject>

class Crank : public QObject {
    Q_OBJECT

public:
    Crank();

    bool getPosition() const;

    void setPosition(const bool);

    void turn(bool, int, int, QVector<int>*);
    void turn(bool, int, QVector<int>*, QVector<int>*);

signals:
    void valueChanged(bool newPosition);
    void resultRegisterChanged(QVector<int>*);
    void counterRegisterChanged(QVector<int>*);

private:
    bool currentPosition;
};

#endif // CRANK_H
