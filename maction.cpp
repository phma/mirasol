#include <iostream>
#include "maction.h"
#include "pattern.h"
using namespace std;

MirasolAction::MirasolAction(QObject *parent,int kind):QAction(parent)
{
  myKind=kind;
  setCheckable(true);
}

void MirasolAction::activate(ActionEvent event)
{
  if (event==QAction::Trigger)
    kindChanged(myKind);
  QAction::activate(event);
}

bool MirasolAction::event(QEvent *e)
{
  //cout<<"button "<<myKind<<" event "<<e->type()<<endl;
  if (e->type()==QEvent::ActionChanged)
    kindChanged(myKind);
  return QAction::event(e);
}

void MirasolAction::setKind(int kind)
{
  setChecked(kind==myKind);
}

void MirasolAction::setNumber(int num)
{
  setEnabled(isKind(num,myKind));
}
