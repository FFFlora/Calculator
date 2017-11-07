#include <QtGui>
#include <QApplication>
#include "calculatorUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int ret = 0;
    CalculatorUI * cal =  CalculatorUI:: NewInstance();


    if(cal!=NULL){

        cal->show();
        ret = a.exec();
        delete cal;
    }

    return ret;


}
