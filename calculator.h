#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <cmath>
#include <iostream>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
    double add(double, double);
    double sub(double, double);
    double mul(double, double);
    double div(double, double);
    void init();
private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void ACButton();
    void DelButton();
    void copyRight();
};
#endif // CALCULATOR_H
