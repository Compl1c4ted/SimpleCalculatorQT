#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    void digitPressed();
    void unaryOperationPressed();
    void binaryOperationPressed();
    void equalsPressed();
    void clearPressed();
private:
    Ui::MainWindow *ui;
    double currentResult;
    QString pendingOperation;
    bool userIsTypingSecondNumber;
};
#endif // MAINWINDOW_H
