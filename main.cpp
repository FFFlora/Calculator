#include <QtGui>
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *w =  new QWidget(NULL, Qt::WindowCloseButtonHint);
    QLineEdit *li = new QLineEdit(w);
    QPushButton *button [20]= {0};
    const char* btnText[20] = {
        "7","8","9","+","(",
        "4","5","6","-",")",
        "1","2","3","*","<-",
        "0",".","=","/","C"
    };
    int ret = 0;
    li->move(10,10);
    li->resize(240,30);
    li->setReadOnly(true);
    for (int i=0;i<4; i++){
        for (int j=0 ; j<5; j++){
            button[i*5 + j] = new QPushButton(w);
            button[i*5 + j]->resize(40,40);
            button[i*5 + j]->move(10+(10+40)*j, 50+(50)*i);
            button[i*5 + j]->setText(btnText[i*5 + j]);
        }
    }
    w->show();
    w->setFixedSize(w->width(),w->height());
    ret = a.exec();
    delete w;
    return ret;


}
