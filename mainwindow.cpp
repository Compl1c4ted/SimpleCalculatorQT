#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentResult(0)
    , pendingOperation("")
    , userIsTypingSecondNumber(false)
{
    ui->setupUi(this);
    connect(ui->zeroButton, &QPushButton::clicked, this, &MainWindow::digitPressed);
    connect(ui->oneButton, &QPushButton::clicked, this, &MainWindow::digitPressed);
    connect(ui->twoButton, &QPushButton::clicked, this, &MainWindow::digitPressed);
    connect(ui->threeButton, &QPushButton::clicked, this, &MainWindow::digitPressed);
    connect(ui->fourButton, &QPushButton::clicked, this, &MainWindow::digitPressed);
    connect(ui->fiveButton, &QPushButton::clicked, this, &MainWindow::digitPressed);
    connect(ui->sixButton, &QPushButton::clicked, this, &MainWindow::digitPressed);
    connect(ui->sevenButton, &QPushButton::clicked, this, &MainWindow::digitPressed);
    connect(ui->ateButton, &QPushButton::clicked, this, &MainWindow::digitPressed);
    connect(ui->nineButton, &QPushButton::clicked, this, &MainWindow::digitPressed);

    connect(ui->plusButton, &QPushButton::clicked, this, &MainWindow::binaryOperationPressed);
    connect(ui->minusButton, &QPushButton::clicked, this, &MainWindow::binaryOperationPressed);
    connect(ui->multiplButton, &QPushButton::clicked, this, &MainWindow::binaryOperationPressed);
    connect(ui->divideButton, &QPushButton::clicked, this, &MainWindow::binaryOperationPressed);

    connect(ui->equalButton, &QPushButton::clicked, this, &MainWindow::equalsPressed);

    connect(ui->clearButton, &QPushButton::clicked,this,&MainWindow::clearPressed);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digitPressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if(!button) return;

    QString digitValue = button->text();
    QString displayValue = ui->output->text();

    if((displayValue == "0") || userIsTypingSecondNumber){
        displayValue = digitValue;
        userIsTypingSecondNumber = false;
    } else {
        displayValue += digitValue;
    }

    ui->output->setText(displayValue);
}


void MainWindow::unaryOperationPressed()
{

}

void MainWindow::binaryOperationPressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    if (!userIsTypingSecondNumber) {
        currentResult = ui->output->text().toDouble();
        pendingOperation = button->text();
        userIsTypingSecondNumber = true;
    } else {
        double operand = ui->output->text().toDouble();
        if(pendingOperation == "+"){
            currentResult += operand;
        } else if(pendingOperation == "-"){
            currentResult -= operand;
        } else if(pendingOperation == "*"){
            currentResult *= operand;
        } else if(pendingOperation == "/"){
            if(operand != 0.0){
                currentResult /= operand;
            } else {

                currentResult = 0.0;
                ui->output->setText("Error");
                pendingOperation.clear();
                return;
            }
        }
        ui->output->setText(QString::number(currentResult));

        pendingOperation = button->text();
        userIsTypingSecondNumber = false;
    }
}

void MainWindow::equalsPressed()
{
    double operand = ui->output->text().toDouble();

    if(pendingOperation == "+"){
        currentResult += operand;
    }else if(pendingOperation == "-"){
        currentResult -= operand;
    }else if(pendingOperation == "*"){
        currentResult *= operand;
    }else if(pendingOperation == "/"){
        if(operand != 0.0){
            currentResult /= operand;
        }else{
            currentResult = 0.0;
        }
    }
    ui->output->setText(QString::number(currentResult));

    pendingOperation.clear();
}

void MainWindow::clearPressed()
{
    currentResult = 0;
    pendingOperation.clear();
    ui->output->clear();
}
