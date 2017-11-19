#include "qcalculatordec.h"
#include <QDebug>
QCalculatorDec::QCalculatorDec()
{
m_exp = "";
m_result = "";
/*QQueue<QString> r = split("+9.11 +(3-1)* -5");
for (int i = 0; i<r.length();i++){
    qDebug()<<r[i];
}*/
}

QCalculatorDec::~QCalculatorDec(){}

bool QCalculatorDec::isDigitOrDot(QChar c){
    return (((c>= "0")&&(c <= '9'))||c == '.') ;
}

bool QCalculatorDec::isSymbol(QChar c){
    return (isOperator(c) || (c == '(')|| (c ==')'));
}

bool QCalculatorDec::isSign(QChar c){
    return ( c == '+' || c == '-');
}

bool QCalculatorDec::isNumber(QString s){
    bool ret = false;
    s.toDouble(&ret);
    return ret;
}

bool QCalculatorDec::isOperator(QString s){
    return (s=='+') || (s == '-') || (s =='*') || (s == '/');
}

bool QCalculatorDec::isLeft(QString s){
    return (s == '(');
}

bool QCalculatorDec::isRight(QString s){
    return (s == ')');

}
int QCalculatorDec::priority(QString s){
    int ret = 0;
    if ((s == '+')||(s == '-')) {
        ret = 1;
    }
    else if ((s == '*')||(s == '/')){
        ret = 2;
    }
    return ret;
}

QQueue<QString> QCalculatorDec::split(const QString &exp){
    QQueue<QString> ret;
    QString num = "";
    QString pre = "";
    for (int i=0; i<exp.length();i++){
        if (isDigitOrDot(exp[i])){
            num += exp[i];
            pre = exp[i];
        }
        else if(isSymbol(exp[i])){
            if (!num.isEmpty()){
                ret.enqueue(num);
                num.clear();
            }
            if (isSign(exp[i]) &&(( pre =="" )||(pre == "(")||isOperator(pre))) {
                num += exp[i];
            }
            else {
                ret.enqueue(exp[i]);
            }
            pre = exp[i];
        }
    }
    if(!num.isEmpty() ){
        ret.enqueue(num);
    }
    return ret;
}
bool QCalculatorDec::match(QQueue<QString>& exp)
{
    bool ret = true;
    QStack<QString> statck;

    for(int i=0; i<exp.length(); i++)
    {
        if(isLeft(exp[i]))//1.是左括号就直接入栈
        {
            statck.push(exp[i]);
        }
        else if(isRight(exp[i]))//2.由括号就判断栈顶元素是不是左括号，是就弹出不要
        {
            if(!statck.isEmpty() && isLeft(statck.top()))
            {
                statck.pop();
            }
            else
            {
                ret = false;
                break;//如果有出错也就没必要往下继续判断了
            }
        }

    }

    return ret && statck.isEmpty();
}
bool QCalculatorDec::transform(QQueue<QString>& exp, QQueue<QString>& output)
{
    bool ret = match(exp);
    QStack<QString> statck;
    output.clear();

    while(ret && !exp.isEmpty())
    {
        QString e = exp.dequeue();
        if(isNumber(e))//1.是数字直接输出
        {
            output.enqueue(e);
        }
        else if(isOperator(e))//2.是操作符先判断优先级
        {
            while(!statck.isEmpty() && (priority(e) <= priority(statck.top())))
            {
                output.enqueue(statck.pop());
            }

            statck.push(e);

        }
        else if(isLeft(e))//3.是左括号直接入栈
        {
            statck.push(e);
        }
        else if(isRight(e))//4.是右括号就把栈元素输出直至遇到左括号
        {
            if(!statck.isEmpty() && (!isLeft(statck.top())))
            {
                output.enqueue(statck.pop());
            }
            if(!statck.isEmpty())
            {
                statck.pop();
            }

        }
        else
        {
            ret = false;
        }
    }

    while (!statck.isEmpty())//5.将栈里剩余的元素全部输出
    {
        output.enqueue(statck.pop());
    }
    if(!ret)
    {
        output.clear();
    }

    return ret;
}

//计算结果
QString QCalculatorDec::calculator(QString lp, QString op, QString rp){
    QString ret = "Error";
    if(isNumber(lp) && isNumber(rp)){
        double l = lp.toDouble();
        double r = rp.toDouble();

        if(op == "+")
        {
            ret.sprintf("%f", l + r);
        }
        else if(op == "-")
        {
            ret.sprintf("%f", l - r);
        }
        else if(op == "*")
        {
            ret.sprintf("%f", l * r);
        }
        else if(op == "/")
        {
            const double p = 0.00000000000001;
            if((-p < r) && (r < p))
            {
                ret = "Error";
            }
            else
            {
                ret.sprintf("%f", l / r);
            }
        }
        else
        {
            ret = "Error";
        }
    }
    return ret;
}
QString QCalculatorDec::calculator(QQueue<QString>& exp)
{
    QString ret = "Error";
    QStack<QString> statck;

    while(!exp.isEmpty())
    {
        QString e = exp.dequeue();

        if( isNumber(e) )//1.若是数字，进栈
        {
            statck.push(e);
        }
        else if( isOperator(e) )//2.是操作符，弹出右操作数，弹出左操作数，将结果入栈
        {
            if( !statck.isEmpty() )
            {
                QString rp = statck.pop();
                QString lp = statck.pop();

                QString result = calculator(lp, e, rp);

                if(result != "Error")
                {
                    statck.push(result);
                }
                else
                {
                    break;
                }
            }
        }
        else//3.else表达式错误
        {
            break;
        }
    }
    if(!statck.isEmpty() && statck.size() == 1 && isNumber(statck.top()))
    {
        ret = statck.pop();
    }
    return ret;
}
bool QCalculatorDec::expression(const QString& exp)
{
    bool ret = false;
    QQueue<QString> spExp = split(exp);
    QQueue<QString> posExp;

    m_exp = exp;

    if(transform(spExp, posExp))
    {
        m_result = calculator(posExp);

        ret = (m_result != "Error");
    }
    else
    {
        m_result = "Error";
    }

    return ret;
}
QString QCalculatorDec::result()
{
    return m_result;
}

