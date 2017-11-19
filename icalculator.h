#ifndef ICALCULATOR_H
#define ICALCULATOR_H
#include <QString>

//定义接口类
//1.提供一个接收输入的接口
//2.提供一个输出结果的接口
//单依赖：接口的具体功能由核心算法类实现，接口由界面文件使用
class ICalculator
{
public:
    virtual bool expression(const QString& exp) = 0;
    virtual QString result() = 0;
};

#endif // ICALCULATOR_H
