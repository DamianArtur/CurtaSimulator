#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication qApplication(argc, argv);

    MainWindow window;
    window.show();

    if (argc == 2) {
        window.openFile(QString(argv[1]));
    }

    return qApplication.exec();;
}
