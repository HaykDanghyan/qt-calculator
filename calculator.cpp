#include "calculator.h"
#include "ui_calculator.h"

using calc = double(Calculator::*)(double, double);

namespace utils {
    double calculationValue = 0.0;
    const int numCount = 10;
    QString expression{};
    bool divTrigger = false;
    bool mulTrigger = false;
    bool addTrigger = false;
    bool subTrigger = false;
    bool sqrtTrigger = false;
    std::map<char, calc> map;
} // utils

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {
    ui->setupUi(this);
    ui->Display->setText(QString::number(utils::calculationValue));
    QPushButton* numButtons[utils::numCount];
    for (int i = 0; i < utils::numCount; ++i) {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton*>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->ButtonDiv, SIGNAL(released()),
            this, SLOT(MathButtonPressed()));
    connect(ui->ButtonMul, SIGNAL(released()),
            this, SLOT(MathButtonPressed()));
    connect(ui->ButtonPlus, SIGNAL(released()),
            this, SLOT(MathButtonPressed()));
    connect(ui->ButtonMinus, SIGNAL(released()),
            this, SLOT(MathButtonPressed()));
    connect(ui->ButtonEqual, SIGNAL(released()),
            this, SLOT(EqualButton()));
    connect(ui->squareRoot, SIGNAL(released()),
            this, SLOT(MathButtonPressed()));
    connect(ui->ButtonAC, SIGNAL(released()),
            this, SLOT(ACButton()));
    connect(ui->Delete, SIGNAL(released()),
            this, SLOT(DelButton()));
    connect(ui->copyright, SIGNAL(released()),
            this, SLOT(copyRight()));
    init();
}

Calculator::~Calculator() {
    delete ui;
    ui = nullptr;
}

void Calculator::NumPressed() {
    QPushButton *button = (QPushButton*)sender();
    QString buttonValue = button->text();
    QString displayValue = ui->Display->text();
    if (displayValue.toDouble() == 0 || displayValue.toDouble() == 0.0) {
        utils::expression += buttonValue;
    } else {
        utils::expression = displayValue + buttonValue;
    }
    ui->Display->setText(utils::expression);
}

void Calculator::MathButtonPressed() {
    utils::divTrigger = false;
    utils::mulTrigger = false;
    utils::addTrigger = false;
    utils::subTrigger = false;
    QString displayValue = ui->Display->text();
    utils::calculationValue = displayValue.toDouble();
    QPushButton* button = (QPushButton*)(sender());
    QString buttonVal = button->text();
    if (QString::compare(buttonVal, "\u00F7", Qt::CaseInsensitive) == 0) {
        utils::divTrigger = true;
    }
    else if (QString::compare(buttonVal, "\u00D7", Qt::CaseInsensitive) == 0) {
        utils::mulTrigger = true;
    }
    else if (QString::compare(buttonVal, "+", Qt::CaseInsensitive) == 0) {
        utils::addTrigger = true;
    }
    else if (QString::compare(buttonVal, "\u221A", Qt::CaseInsensitive) == 0){
        utils::sqrtTrigger = true;
    } else {
        utils::subTrigger = true;
    }
    utils::expression += buttonVal;
    ui->Display->setText(utils::expression);
}

void Calculator::EqualButton() {
    double solution = 0.0;
    std::string tmp = utils::expression.toStdString();
    if (!(tmp[tmp.length() - 1] >= '0' && tmp[tmp.length() - 1] <= '9')) {
        ui->Display->setText("Syntax Error");
        return;
    }
    if (!(tmp[0] >= '0' && tmp[0] <= '9') && tmp.length() == 1) {
        ui->Display->setText("Syntax Error");
        return;
    }
    if (utils::expression.indexOf('\u00F7') != -1) {

    }
    else if (utils::expression.indexOf('\u00D7') != -1) {

    }
    else if (utils::expression.indexOf('-') != -1) {

    }
    else if (utils::expression.indexOf('+') != -1) {
        auto pos = utils::expression.indexOf('+');
        auto leftArg = std::stod(utils::expression.toStdString().substr(0, pos));
        auto rightArg = std::stod(utils::expression.
           toStdString().substr(pos + 1));
        solution = (this->*utils::map['+'])(leftArg, rightArg);
    }
    else if (utils::sqrtTrigger) {
        QString number{};
        for (int i = 1; i < utils::expression.length(); ++i) {
            number[i - 1] = utils::expression[i];
        }
        double num = number.toDouble();
        solution = std::sqrt(num);
    } else {

    }
    utils::expression = QString::number(solution);
    ui->Display->setText(utils::expression);
}

void Calculator::ACButton() {
    utils::expression = "";
    ui->Display->setText(QString::number(0));
}

void Calculator::DelButton() {
    QString tmp{};
    for (int i = 0; i < utils::expression.length() - 1; ++i) {
        tmp += utils::expression[i];
    }
    if (utils::expression.length() == 0) {
        ui->Display->setText(QString::number(0));
        return;
    }
    utils::expression = std::move(tmp);
    ui->Display->setText(utils::expression);
}

void Calculator::init() {
    utils::map['+'] = &Calculator::add;
    utils::map['\u00D7'] = &Calculator::mul;
    utils::map['-'] = &Calculator::sub;
    utils::map['\u00F7'] = &Calculator::div;
}

double Calculator::add(double num1, double num2) {
    return num1 + num2;
}

double Calculator::sub(double num1, double num2) {
    return num1 - num2;
}

double Calculator::mul(double num1, double num2) {
    return num1 * num2;
}

double Calculator::div(double num1, double num2) {
    return num1 / num2;
}

void Calculator::copyRight() {
    ui->Display->setText("Created by Danghyan Hayk");
}
