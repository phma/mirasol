/******************************************************/
/*                                                    */
/* maction.h - button actions for showing numbers     */
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
#ifndef MACTION_H
#define MACTION_H
#include <QtWidgets>

class MirasolAction: public QAction
{
  Q_OBJECT
public:
  MirasolAction(QObject *parent=nullptr,int kind=0);
  void activate(ActionEvent event);
public slots:
  void setKind(int kind); // sets checked if kind matches myKind
  void setNumber(int num); // sets enabled if num is my kind of number
signals:
  void kindChanged(int kind); // emitted on activate(triggered)
protected:
  bool event(QEvent *e);
private:
  int myKind;
};
#endif
