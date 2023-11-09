#ifndef INPUTREGISTER_H
#define INPUTREGISTER_H

#include <QObject>
#include <QSlider>

#define INPUT_REGISTER_SIZE 8

class InputRegister : public QObject {
    Q_OBJECT

public:
    InputRegister();

    QVector<int>* getValues() const;
    int getValue(int number) const;

    void setValue(const int number, const int newValue);

signals:
    void valueChanged(int number, int newValue);

private:
    QVector<int>* values;
};

#endif // INPUTREGISTER_H
