/******************************************************/
/*                                                    */
/* maction.cpp - button actions for showing numbers   */
/*                                                    */
/******************************************************/
/* Copyright 2017 Pierre Abbat.
 * This file is part of Mirasol.
 * 
 * Mirasol is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Mirasol is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Mirasol. If not, see <http://www.gnu.org/licenses/>.
 */
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
