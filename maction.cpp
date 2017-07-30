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

void MirasolAction::setKind(int kind)
{
  setChecked(kind==myKind);
}

void MirasolAction::setNumber(int num)
{
  setEnabled(isKind(num,myKind));
}
