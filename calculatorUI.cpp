#include "calculatorUI.h"
#include <QDebug>
CalculatorUI::CalculatorUI() : QWidget(NULL, Qt::WindowCloseButtonHint)
{

}


 CalculatorUI* CalculatorUI::NewInstance(){
    CalculatorUI *ret = new CalculatorUI();
    if ( (ret==NULL)||!ret->construct()){
        delete ret;
        ret = NULL;
    }
    return ret;
};

bool CalculatorUI::construct(){
    bool ret = true;
    const char* btnText[20] = {
        "7","8","9","+","(",
        "4","5","6","-",")",
        "1","2","3","*","<-",
        "0",".","=","/","C"
    };
    m_edit = new QLineEdit(this);
    if(m_edit!=NULL){
        m_edit->move(10,10);
        m_edit->resize(240,30);
        m_edit->setReadOnly(true);
    }
    else ret = false;
    for (int i=0;(i<4)&& ret; i++){
        for (int j=0 ; j<5 && ret; j++){
            m_button[i*5 + j] = new QPushButton(this);
            if (m_button[i*5+j]!= NULL){
                m_button[i*5 + j]->resize(40,40);
                m_button[i*5 + j]->move(10+(10+40)*j, 50+(50)*i);
                m_button[i*5 + j]->setText(btnText[i*5 + j]);
                connect(m_button[i*5 + j],SIGNAL(clicked()),this, SLOT(onButtonClicked()));
            }
            else ret = false;
        }
    }

    return ret;
}


void CalculatorUI::onButtonClicked(){
    QPushButton *btn = (QPushButton*)sender();
    qDebug()<<"onButtonClicked()";
    qDebug()<<btn->text();
}
CalculatorUI::~CalculatorUI(){


}
