#ifndef QCALCULATORDEC_H
#define QCALCULATORDEC_H

#include <QString>
#include <QStack>
#include <QQueue>

class QCalculatorDec
{
protected:
QString m_exp;
QString m_result;

bool isDigitOrDot(QChar c);
bool isSymbol(QChar c);
bool isSign(QChar c);
bool isNumber(QString s);
bool isOperator (QString s);
bool isLeft(QString s);
bool isRight (QString s);
int priority(QString s);
QQueue<QString> split(const QString &exp);
public:
    QCalculatorDec();
    ~QCalculatorDec();
    bool expression(const QString&exp);
    QString expression();
    QString result();
};

#endif // QCALCULATORDEC_H
