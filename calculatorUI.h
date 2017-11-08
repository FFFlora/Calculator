#ifndef __CALCULATORUI_H__
#define __CALCULATORUI_H__

#include <QWidget>
#include <QtGui>
#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

class CalculatorUI : public QWidget
{
    Q_OBJECT
private:
    QLineEdit *m_edit;
    QPushButton * m_button[20];
    CalculatorUI();
    bool construct();
private slots:
    void onButtonClicked();
public:
   static CalculatorUI* NewInstance();
    ~CalculatorUI();
    void show(){
        QWidget::show();
        setFixedSize(width(),height());
    }

};

#endif // CALCULATORUI_H
