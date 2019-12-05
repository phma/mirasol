/******************************************************/
/*                                                    */
/* mwidget.h - main window class                      */
/*                                                    */
/******************************************************/
/* Copyright 2015,2017 Pierre Abbat.
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
#include <QMainWindow>
#include <QTimer>
#include <vector>
#include <queue>
#include "dotcanvas.h"
#include "maction.h"
#include "trajectory.h"

class MirasolWidget: public QMainWindow
{
  Q_OBJECT
public:
  DotCanvas *dotcanvas;
  QToolBar *toolbar;
  std::vector<MirasolAction *> actions;
  QAction *exitAction,*upAction,*downAction;
  QAction *aboutProgramAction,*aboutQtAction;
  QTimer *timer;
  QMenu *fileMenu,*baseMenu,*kindMenu,*numberMenu,*helpMenu;
  MirasolWidget(QWidget *parent=0);
  ~MirasolWidget();
  void makeActions();
  void unmakeActions();
  void queuePattern(DotList pattern,int kind);
signals:
  void numberChanged(int num);
  void kindChanged(int kind);
public slots:
  void setNumber(int num);
  void setNumber(const QString &newtext);
  void increaseNumber(bool checked);
  void decreaseNumber(bool checked);
  void prepareSetKind(int kind);
  void setKind(bool checked);
  void animateDots();
  void aboutProgram();
  void aboutQt();
private:
  int numDots;
  int maxNumDots;
  int kindDots;
  int preKindDots; // set by one signal in preparation for another signal, which has no argument
  int changeTime,noChangeTime;
  std::queue<MultiTrajectory> dotsQueue;
  DotList lastDots;
  DotPixmap *pixmap;
};
