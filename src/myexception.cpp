#include "myexception.h"

const char* MyException::what() {
    return errorMessage.toLocal8Bit().constData();
}
