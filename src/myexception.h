#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <exception>
#include <QString>

class MyException : public std::exception {

public:
    template<class T>
    MyException(T exceptionText) {
        errorMessage = QString(exceptionText);
    }

    const char* what();

private:
    QString errorMessage;
};

#endif // MYEXCEPTION_H
