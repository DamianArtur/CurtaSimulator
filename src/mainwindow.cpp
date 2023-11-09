#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , inputRegister(new InputRegister())
    , counterRegister(new CounterRegister())
    , resultRegister(new ResultRegister())
    , carriage(new Carriage())
    , counterSwitch(new CounterSwitch())
    , crank(new Crank())
{
    ui->setupUi(this);

    // input register
    for(int i = 0; i < 8; i++) {
        QString sliderName = QString("settingSlider") + QString::number(i);
        QSlider* slider = MainWindow::findChild<QSlider *>(sliderName);
        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(inputSliderChanged(int)));
    }

    connect(inputRegister, SIGNAL(valueChanged(int,int)), this, SLOT(setInputLabel(int,int)));

    // counter switch
    QSlider* switchSlider = MainWindow::findChild<QSlider *>(QString("counterSwitchSlider"));

    connect(switchSlider, SIGNAL(valueChanged(int)), this, SLOT(counterSwitchSliderChanged(int)));

    connect(counterSwitch, SIGNAL(valueChanged(int)), SLOT(setCounterSwitchSlider(int)));

    // carriage
    QPushButton* buttonCarriageLeft = MainWindow::findChild<QPushButton *>(QString("buttonCarriageLeft"));
    QPushButton* buttonCarriageRight = MainWindow::findChild<QPushButton *>(QString("buttonCarriageRight"));

    connect(buttonCarriageLeft, SIGNAL(released()), this, SLOT(carriageButtonClicked()));
    connect(buttonCarriageRight, SIGNAL(released()), this, SLOT(carriageButtonClicked()));

    connect(carriage, SIGNAL(valueChanged(int)), this, SLOT(setCarriageLabels(int)));

    // crank
    QPushButton *crankButton = MainWindow::findChild<QPushButton *>(QString("buttonCrankPosition"));

    connect(crankButton, SIGNAL(released()), this, SLOT(crankSwitchButtonClicked()));

    connect(crank, SIGNAL(valueChanged(bool)), this, SLOT(setCrankSwitch(bool)));

    QPushButton* crankHandleButton = MainWindow::findChild<QPushButton *>(QString("buttonCrankHandle"));

    connect(crankHandleButton, SIGNAL(released()), this, SLOT(crankButtonClicked()));

    connect(crank, SIGNAL(counterRegisterChanged(QVector<int>*)), this, SLOT(setCounterRegisterLabel(QVector<int>*)));
    connect(crank, SIGNAL(resultRegisterChanged(QVector<int>*)), this, SLOT(setResultRegisterLabel(QVector<int>*)));

    // clear buttons
    QPushButton* buttonClearCounter = MainWindow::findChild<QPushButton *>(QString("buttonClearCounter"));
    QPushButton* buttonClearResult = MainWindow::findChild<QPushButton *>(QString("buttonClearResult"));

    connect(buttonClearCounter, SIGNAL(released()), this, SLOT(clearCounterButtonClicked()));
    connect(buttonClearResult, SIGNAL(released()), this, SLOT(clearResultButtonClicked()));

    connect(counterRegister, SIGNAL(valueChanged(QVector<int>*)), this, SLOT(setCounterRegisterLabel(QVector<int>*)));
    connect(resultRegister, SIGNAL(valueChanged(QVector<int>*)), this, SLOT(setResultRegisterLabel(QVector<int>*)));

    // menu file
    QAction* saveAction = MainWindow::findChild<QAction *>(QString("actionSave"));
    QAction* openAction = MainWindow::findChild<QAction *>(QString("actionOpen"));

    connect(saveAction, SIGNAL(triggered()), this, SLOT(actionSaveClicked()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(actionOpenClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile(QString fileName) {
    actionOpenClicked(fileName);
}

// -------------------------------------------------

void MainWindow::inputSliderChanged(int newValue) {
    QSlider* slider = (QSlider*)sender();
    QString sliderName = slider->objectName();
    int number = sliderName[sliderName.size()-1].digitValue();
    inputRegister->setValue(number, newValue);
}

void MainWindow::setInputLabel(int number, int newValue) {
    QString labelName = QString("inputLabel") + QString::number(number);
    QLabel* label = MainWindow::findChild<QLabel *>(labelName);
    label->setText(QString::number(newValue));
}

void MainWindow::setInputSlider(QVector<int>* data) {
    for(int i = 0; i < (*data).size(); i++) {
        QString sliderName = QString("settingSlider") + QString::number(i);
        QSlider* slider = MainWindow::findChild<QSlider *>(sliderName);
        slider->setValue((*data)[i]);
    }
}

// -------------------------------------------------

void MainWindow::carriageButtonClicked() {
    QPushButton* button = (QPushButton*)sender();
    QString buttonName = button->objectName();
    if (buttonName == QString("buttonCarriageLeft")) {
        (*carriage)++;
    } else {
        (*carriage)--;
    }
}

void MainWindow::setCarriageLabels(int newPosition) {
    newPosition--;
    for (int i = 0; i < 10; i++) {
        QString labelName = QString("carriageIndicator") + QString::number(i);
        QLabel* label = MainWindow::findChild<QLabel *>(labelName);
        if (newPosition > 0) {
            label->setText(QString::number(newPosition));
        } else {
            label->setText(QString(""));

        }
        newPosition++;
    }
}

// -------------------------------------------------

void MainWindow::counterSwitchSliderChanged(int newPosition) {
    counterSwitch->setValue(newPosition);
}

void MainWindow::setCounterSwitchSlider(int newValue) {
    QSlider* slider = MainWindow::findChild<QSlider *>("counterSwitchSlider");
    slider->setValue(newValue);
}

// -------------------------------------------------

void MainWindow::crankSwitchButtonClicked() {
    if (crank->getPosition() == ADDITION) {
        crank->setPosition(SUBTRACTION);
    } else {
        crank->setPosition(ADDITION);
    }
}

void MainWindow::setCrankSwitch(bool newPosition) {
    QPushButton* crankButton = MainWindow::findChild<QPushButton *>(QString("buttonCrankPosition"));
    if (newPosition) {
        crankButton->setText(QString(">>> Addition <<<"));
    } else {
        crankButton->setText(QString(">>> Subtraction <<<"));
    }
}

// -------------------------------------------------

void MainWindow::crankButtonClicked() {
    crank->turn(crank->getPosition(), counterSwitch->getValue(), carriage->getPosition(), counterRegister->getValues());
    crank->turn(crank->getPosition(), carriage->getPosition(), inputRegister->getValues(), resultRegister->getValues());
}

// -------------------------------------------------

void MainWindow::clearCounterButtonClicked() {
    counterRegister->clear();
}

void MainWindow::setCounterRegisterLabel(QVector<int>* values) {
    for (int i = 0; i < 6; i++) {
        QString labelName = QString("counterLabel") + QString::number(i);
        QLabel* label = MainWindow::findChild<QLabel *>(labelName);
        label->setText(QString::number((*values)[i]));
    }
}

// -------------------------------------------------

void MainWindow::clearResultButtonClicked() {
    resultRegister->clear();
}

void MainWindow::setResultRegisterLabel(QVector<int>* values) {
    for (int i = 0; i < 11; i++) {
        QString labelName = QString("resultLabel") + QString::number(i);
        QLabel* label = MainWindow::findChild<QLabel *>(labelName);
        label->setText(QString::number((*values)[i]));
    }
}

// -------------------------------------------------

void MainWindow::actionSaveClicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    QTextStream out(&file);

    QVector<int>* inputRegisterData = inputRegister->getValues();
    for (int i = 0; i < 7; i++) {
        out << (*inputRegisterData)[i] << ",";
    }
    out << (*inputRegisterData)[7] << "\n";

    out << QString::number(carriage->getPosition()) << "\n";

    QVector<int> *counterRegisterData = counterRegister->getValues();
    for (int i = 0; i < 5; i++) {
        out << (*counterRegisterData)[i] << ",";
    }
    out << (*counterRegisterData)[5] << "\n";

    QVector<int> *resultRegisterData = resultRegister->getValues();
    for (int i = 0; i < 10; i++) {
        out << (*resultRegisterData)[i] << ",";
    }
    out << (*resultRegisterData)[10] << "\n";

    if (crank->getPosition()) {
        out << "addition\n";
    } else {
        out << "subtraction\n";
    }

    if (counterSwitch->getValue() == 0) {
        out << "addition";
    } else {
        out << "subtraction";
    }

    file.close();
}

void MainWindow::actionOpenClicked(QString fileName) {
    if (fileName == "") {
         fileName = QFileDialog::getOpenFileName(this, "Open the file");
    }

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();

    try {
        QVector<QString> textData = text.split("\n").toVector();
        if (textData.size() != 6) {
            throw MyException("Data in file isn't valid!");
        }

        QVector<int>* inputRegisterData = inputRegister->getValues();
        QVector<QString> inputRegisterNewData = textData[0].split(",").toVector();
        if (inputRegisterNewData.size() != 8) {
            throw MyException("Input Register data isn't valid!");
        }
        for (int i = 0; i < 8; i++) {
            (*inputRegisterData)[i] = (inputRegisterNewData[i]).toInt();
        }
        setInputSlider(inputRegisterData);

        int newCarriageValue = textData[1].toInt();
        if (newCarriageValue < 1 || newCarriageValue > 6) {
            throw MyException("Carriage position isn't valid!");
        }
        carriage->setPosition(newCarriageValue);

        QVector<int>* counterRegisterData = counterRegister->getValues();
        QVector<QString> counterRegisterNewData = textData[2].split(",").toVector();
        if (counterRegisterNewData.size() != 6) {
            throw MyException("Counter Register data isn't valid!");
        }
        for (int i = 0; i < 6; i++) {
            (*counterRegisterData)[i] = (counterRegisterNewData[i]).toInt();
        }
        setCounterRegisterLabel(counterRegisterData);

        QVector<int>* resultRegisterData = resultRegister->getValues();
        QVector<QString> resultRegisterNewData = textData[3].split(",").toVector();
        if (resultRegisterNewData.size() != 11 ){
            throw MyException("Result Register data isn't valid!");
        }
        for (int i = 0; i < 11; i++) {
            (*resultRegisterData)[i] = (resultRegisterNewData[i]).toInt();
        }
        setResultRegisterLabel(resultRegisterData);

        if(textData[4] == "addition") {
            crank->setPosition(true);
        } else {
            crank->setPosition(false);
        }

        if(textData[5] == "addition") {
            counterSwitch->setValue(0);
        } else {
            counterSwitch->setValue(1);
        }
    }
    catch (MyException &myException ) {
        QMessageBox::warning(this, "Warning", QString("Cannot open file: ") + QString(myException.what()));
    }
    file.close();
}
