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
/*
 #### 解决经典问题：Object::conect: No such slot...
 * 检查class 是否继承于QObject
 * 检查class 声明开始处是否添加 Q_OBJECT
 * 检查是否使用slots关键字进行SLOT声明
 * 检查SLOT的名称是否拼写错误
 * 重新执行qmake
*/


