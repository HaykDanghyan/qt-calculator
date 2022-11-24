#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Calculator calculate;
    calculate.setFixedSize(calculate.size());
    calculate.show();
    return a.exec();
}
