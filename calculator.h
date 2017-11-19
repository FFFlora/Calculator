#ifndef QCalculator_H
#define QCalculator_H
#include "qcalculatordec.h"
#include "calculatorUI.h"

//实现界面类与计算逻辑类的关联
class QCalculator
{
protected:
    calculatorUI* m_ui;//用指针的原因是它使用二阶构造
    QCalculatorDec m_cal;
    QCalculator();
    bool construct();

public:
    static QCalculator* NewInstance();//成员有二阶构造，使用它的类也要二阶构造
    void show();
    ~QCalculator();
};

#endif // QCalculator_H
