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
  setnumber(240);
  setCentralWidget(dotcanvas);
  dotcanvas->show();
  connect(inpline,SIGNAL(textChanged(QString)),this,SLOT(setnumber(QString)));
}

void MirasolWidget::setnumber(int num)
{
  cout<<num<<endl;
  dotcanvas->setDots(squarePronicPattern(num));
}

void MirasolWidget::setnumber(const QString &newtext)
{
  setnumber(newtext.toInt());
}

/* The buttons are labeled with the following numbers in the appropriate pattern:
 * Asteraceous (which is considered base 0): 35.
 * All bases (which may range from 6 to 34): 35.
 * Prime: 37 (in the asteraceous pattern).
 * Composite: 36.
 * Square: 36.
 * Pronic: 30.
 * Triangular: 36.
 * Hexagonal: 37.
 * Fibonacci: 34.
 */
