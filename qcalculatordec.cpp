#include "qcalculatordec.h"
QCalculatorDec::QCalculatorDec()
{
m_exp = "";
m_result = "";
}

QCalculatorDec::~QCalculatorDec(){}

bool QCalculatorDec::isDigitOrDot(QChar c){
    return ((c>= "0")&&(c <= '9')||c == '.' );
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
bool QCalculatorDec::priority(QString s){
    int ret = 0;
    if ((s == '+')||(s == '-')) {
        ret = 1;
    }
    else if ((s == '*')||(s == '/')){
        ret = 2;
    }
    return ret;
}
