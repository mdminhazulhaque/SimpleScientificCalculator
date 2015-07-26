#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>
#include <QDebug>
#include "lepton/Lepton.h"

namespace Ui {
class Calculator;
}

class Calculator : public QDialog
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

private slots:
    void numberButtonClicked();
    void operationButtonClicked();
    void parenthesisButtonClicked();
    void functionButtonClicked();
    void removeLastChar();
    void powerButtonClicked();
    void acButtonClicked();
    void memoryButtonClicked();
    void factButtonClicked();
    void dotButtonClicked();
    void evaluate();

private:
    Ui::Calculator *ui;
    Lepton::Parser parser;
    bool clear;
    qreal memory;
};

#endif // CALCULATOR_H
