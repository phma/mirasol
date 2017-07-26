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
  //dotcanvas->setDots(dots);
  setnumber(64);
  setCentralWidget(dotcanvas);
  dotcanvas->show();
  connect(inpline,SIGNAL(textChanged(QString)),this,SLOT(setnumber(QString)));
}

void MirasolWidget::setnumber(int num)
{
  cout<<num<<endl;
  dotcanvas->setDots(basePattern(num,10));
}

void MirasolWidget::setnumber(const QString &newtext)
{
  setnumber(newtext.toInt());
}
