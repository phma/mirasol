#include <iostream>
#include "mwidget.h"
using namespace std;

MirasolWidget::MirasolWidget(QWidget *parent):QWidget(parent)
{
  resize(320,240);
  setWindowTitle(QApplication::translate("main", "Mirasol"));
  show();
  inpline=new QLineEdit(this);
  inpline->show();
  button = new QPushButton(QApplication::translate("main", "Show number"),this);
  button->move(216,0);
  button->show();
  connect(inpline,&QLineEdit::textChanged,this,&MirasolWidget::setnumber);
}

void MirasolWidget::setnumber(const QString &newtext)
{
  cout<<newtext.toStdString()<<endl;
}