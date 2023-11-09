#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inputregister.h"
#include "counterregister.h"
#include "resultregister.h"
#include "carriage.h"
#include "counterswitch.h"
#include "crank.h"
#include "myexception.h"

#include <QMainWindow>
#include <QSlider>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void openFile(QString fileName);

private:

    Ui::MainWindow *ui;

    InputRegister* inputRegister;

    CounterRegister* counterRegister;

    ResultRegister* resultRegister;

    Carriage* carriage;

    CounterSwitch* counterSwitch;

    Crank* crank;

private slots:
    void inputSliderChanged(int newValue);

    void setInputLabel(int number, int newValue);

    void setInputSlider(QVector<int>*);

    //------------------------------------

    void carriageButtonClicked();

    void setCarriageLabels(int newPosition);

    //------------------------------------

    void counterSwitchSliderChanged(const int);

    void setCounterSwitchSlider(int);

    //------------------------------------

    void crankSwitchButtonClicked();

    void setCrankSwitch(bool newPosition);

    //------------------------------------

    void crankButtonClicked();

    //------------------------------------

    void clearCounterButtonClicked();

    void setCounterRegisterLabel(QVector<int>*);

    //------------------------------------

    void clearResultButtonClicked();

    void setResultRegisterLabel(QVector<int>*);

    //------------------------------------

    void actionSaveClicked();

    void actionOpenClicked(QString fileName = QString(""));

};
#endif // MAINWINDOW_H
