#include "calculatorUI.h"
#include <QDebug>
CalculatorUI::CalculatorUI() : QWidget(NULL, Qt::WindowCloseButtonHint)
{
m_cal = NULL;
}


CalculatorUI* CalculatorUI::NewInstance(){
    CalculatorUI *ret = new CalculatorUI();
    if ( (ret==NULL)||!ret->construct()){
        delete ret;
        ret = NULL;
    }
    return ret;
}

bool CalculatorUI::construct(){
    bool ret = true;
    m_edit = new QLineEdit(this);//父组件是this的原因：组合关系，同生死共存亡
    const char* btnText[20] = {
        "7","8","9","+","(",
        "4","5","6","-",")",
        "1","2","3","*","<-",
        "0",".","=","/","C"
    };


    if(m_edit!=NULL){
        m_edit->move(10,10);
        m_edit->resize(240,30);
        m_edit->setReadOnly(true);
        m_edit->setAlignment(Qt::AlignRight);//右对齐
    }
    else{ ret = false;}
    for (int i=0;(i<4)&& ret; i++){
        for (int j=0 ; j<5 && ret; j++){
            m_button[i*5 + j] = new QPushButton(this);
            if (m_button[i*5+j]!= NULL){
                m_button[i*5 + j]->resize(40,40);
                m_button[i*5 + j]->move(10+(10+40)*j, 50+(50)*i);
                m_button[i*5 + j]->setText(btnText[i*5 + j]);
                connect(m_button[i*5 + j],SIGNAL(clicked()),this, SLOT(onButtonClicked()));
            }
            else {ret = false;}
        }
    }

    return ret;
}

void CalculatorUI::onButtonClicked(){

    QPushButton *btn =dynamic_cast< QPushButton*>( sender());
    QString text = m_edit->text()+ btn->text();
    if(btn!=NULL){
        QString clickedText = btn->text();
        if ( clickedText == "<-"){
            QString text = m_edit->text();
            if (text.length() > 0){
                text.remove(text.length()-1,1);
                m_edit->setText(text);
            }
            else if (text.length() == 0){
                m_edit->setText("");
            }
        }
        else if (clickedText == "C"){
            m_edit ->setText("");
        }
        else if (clickedText == "="){
            if(m_cal != NULL){
                m_cal ->expression(m_edit ->text());
                m_edit->setText(m_cal->result());
            }

        }
        else {
            m_edit->setText(m_edit->text() +clickedText);
        }
    }
}

void CalculatorUI::setCalculator(ICalculator* cal)
{
    m_cal = cal;
}
ICalculator* CalculatorUI::getCalculator(){
    return m_cal;
}

CalculatorUI::~CalculatorUI(){


}
