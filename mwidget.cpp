#include <iostream>
#include "mwidget.h"
#include "pattern.h"
using namespace std;

MirasolWidget::MirasolWidget(QWidget *parent):QMainWindow(parent)
{
  DotList dots;
  int i,j;
  resize(320,240);
  setWindowTitle(QApplication::translate("main", "Mirasol"));
  show();
  inpline=new QLineEdit(this);
  inpline->setBackgroundRole(QPalette::Base);
  //inpline->show();
  button = new QPushButton(QApplication::translate("main", "Show number"),this);
  button->move(216,0);
  //button->show();
  dotcanvas=new DotCanvas(this);
  for (i=-1;i<2;i++)
    for (j=-1;j<2;j++)
      dots+=xy(i,j);
  dotcanvas->setDots(dots);
  setCentralWidget(dotcanvas);
  dotcanvas->show();
  connect(inpline,&QLineEdit::textChanged,this,&MirasolWidget::setnumber);
}

void MirasolWidget::setnumber(const QString &newtext)
{
  cout<<newtext.toStdString()<<endl;
  dotcanvas->setDots(aster(newtext.toInt()));
}
