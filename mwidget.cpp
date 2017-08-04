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
  toolbar=new QToolBar(this);
  dotcanvas=new DotCanvas(this);
  for (i=-1;i<2;i++)
    for (j=-1;j<2;j++)
      dots+=xy(i,j);
  setnumber(30);
  setCentralWidget(dotcanvas);
  addToolBar(Qt::TopToolBarArea,toolbar);
  dotcanvas->show();
  makeActions();
  //connect(inpline,SIGNAL(textChanged(QString)),this,SLOT(setnumber(QString)));
}

MirasolWidget::~MirasolWidget()
{
  unmakeActions();
  delete dotcanvas;
  delete toolbar;
}

void MirasolWidget::setnumber(int num)
{
  cout<<num<<endl;
  dotcanvas->setDots(smooth5Pattern(num));
}

void MirasolWidget::setnumber(const QString &newtext)
{
  setnumber(newtext.toInt());
}

/* The buttons are labeled with the following numbers in the appropriate pattern:
 * Asteraceous (which is considered base 0): 35.
 * All bases (which may range from 6 to 34): 35.
 * Composite: 36.
 * Prime: 37 (in the asteraceous pattern).
 * Fibonacci: 34.
 * Square: 36.
 * Pronic: 30.
 * Triangular: 36.
 * Hexagonal: 37.
 * 5-Smooth: 30.
 */
int shownNumbers[]={35,36,37,34,36,30,36,37,30};

void MirasolWidget::makeActions()
{
  int i;
  if (actions.size()==0)
  {
    actions.push_back(new MirasolAction(this,0));
    actions.push_back(new MirasolAction(this,10));
    actions.push_back(new MirasolAction(this,16));
    for (i=1;i<=NUM_KINDS;i++)
      actions.push_back(new MirasolAction(this,-i));
  }
}

void MirasolWidget::unmakeActions()
{
  int i;
  for (i=0;i<actions.size();i++)
    delete actions[i];
  actions.resize(0);
}
