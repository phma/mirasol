/******************************************************/
/*                                                    */
/* mwidget.cpp - main window class                    */
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
#include <iostream>
#include "mwidget.h"
#include "pattern.h"
using namespace std;

MirasolWidget::MirasolWidget(QWidget *parent):QMainWindow(parent)
{
  int i,j;
  maxNumDots=1000;
  resize(707,500);
  setWindowTitle(QApplication::translate("main", "Mirasol"));
  show();
  pixmap=new DotPixmap(256,256);
  toolbar=new QToolBar(this);
  toolbar->setIconSize(QSize(40,40));
  dotcanvas=new DotCanvas(this);
  timer=new QTimer(this);
  setCentralWidget(dotcanvas);
  addToolBar(Qt::TopToolBarArea,toolbar);
  dotcanvas->show();
  makeActions();
  changeTime=64; // ms that a static MultiTrajectory runs when the new number is different
  noChangeTime=32; // set short time temporarily so that it won't spend two seconds drawing nothing
  setNumber(0);
  prepareSetKind(0);
  setKind(true);
  noChangeTime=1000; // ms that a moving MultiTrajectory runs when the number isn't changed but the pattern is
  timer->start(changeTime);
  connect(timer,SIGNAL(timeout()),this,SLOT(animateDots()));
}

MirasolWidget::~MirasolWidget()
{
  unmakeActions();
  delete dotcanvas;
  delete toolbar;
  delete pixmap;
}

void MirasolWidget::setNumber(int num)
{
  if (numDots!=num)
  {
    numDots=num;
    //dotcanvas->setDots(kindPattern(numDots,kindDots));
    queuePattern(kindPattern(numDots,kindDots),kindDots);
    numberChanged(num);
  }
}

void MirasolWidget::prepareSetKind(int kind)
{
  //cout<<"kind="<<kind<<endl;
  preKindDots=kind;
}

void MirasolWidget::setKind(bool checked)
{
  //cout<<"kind="<<preKindDots<<endl;
  if (kindDots!=preKindDots)
  {
    kindDots=preKindDots;
    //dotcanvas->setDots(kindPattern(numDots,kindDots));
    queuePattern(kindPattern(numDots,kindDots),kindDots);
    kindChanged(kindDots);
  }
}

void MirasolWidget::queuePattern(DotList pattern,int kind)
{
  DotList startPattern;
  QTime startTime;
  int duration;
  if (dotsQueue.empty())
  {
    startTime=QDateTime::currentDateTimeUtc().time();
    startTime=startTime.addMSecs(changeTime);
    startPattern=lastDots;
  }
  else
  {
    startTime=dotsQueue.back().getEndTime();
    startPattern=dotsQueue.back().atTime(startTime);
  }
  if (startPattern.size()==pattern.size())
    duration=noChangeTime;
  else
  {
    duration=changeTime;
    startPattern=pattern;
  }
  MultiTrajectory traj(startPattern,0,pattern);
  //traj.bendAvoid();
  traj.setTime(startTime,duration);
  traj.setKind(kind);
  dotsQueue.push(traj);
}

void MirasolWidget::animateDots()
{
  QTime now;
  QString timeStr;
  bool popped;
  int lastKind;
  now=QDateTime::currentDateTimeUtc().time();
  /* QTime::currentTime returns local, which will cause problems on
   * Adenauer Day and Auerbach Day.
   */
  //timeStr=now.toString(Qt::ISODate);
  //cout<<timeStr.toStdString()<<'\r';
  cout<<dotsQueue.size()<<"  \r";
  cout.flush();
  if (dotsQueue.size())
  {
    do
    {
      popped=false;
      lastDots=dotsQueue.front().atTime(now);
      lastKind=dotsQueue.front().getKind();
      if (dotsQueue.front().foreAft(now)==1)
      {
        dotsQueue.pop();
        popped=true;
      }
    } while (dotsQueue.size() && popped);
    dotcanvas->setDots(lastDots);
    timer->setInterval(0);
    if (dotsQueue.empty())
    {
      kindChanged(lastKind);
      //cout<<"Set kind to "<<lastKind<<endl;
    }
  }
  else
    timer->setInterval(changeTime);
}

void MirasolWidget::setNumber(const QString &newtext)
{
  setNumber(newtext.toInt());
}

void MirasolWidget::increaseNumber(bool checked)
{
  int i;
  for (i=numDots+1;i<=maxNumDots && !isKind(i,kindDots);i++);
  if (i<=maxNumDots)
    setNumber(i);
}

void MirasolWidget::decreaseNumber(bool checked)
{
  int i;
  for (i=numDots-1;i>=0 && !isKind(i,kindDots);i--);
  if (i>=0)
    setNumber(i);
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
  vector<int> kindlist;
  if (actions.size()==0)
  {
    fileMenu=menuBar()->addMenu(tr("&File"));
    baseMenu=menuBar()->addMenu(tr("&Base"));
    kindMenu=menuBar()->addMenu(tr("&Kind of Number"));
    numberMenu=menuBar()->addMenu(tr("&Number"));
    kindlist.push_back(0);
    kindlist.push_back(10);
    kindlist.push_back(16);
    for (i=1;i<=NUM_KINDS;i++)
      kindlist.push_back(-i);
    for (i=0;i<kindlist.size();i++)
    {
      pixmap->setDots(kindPattern(shownNumbers[(kindlist[i]>0)?0:-kindlist[i]],kindlist[i]));
      pixmap->paintDots();
      actions.push_back(new MirasolAction(this,kindlist[i]));
      actions.back()->setIcon(QIcon(*pixmap));
      connect(actions.back(),SIGNAL(triggered(bool)),this,SLOT(setKind(bool)));
      connect(actions.back(),SIGNAL(kindChanged(int)),this,SLOT(prepareSetKind(int)));
      connect(this,SIGNAL(kindChanged(int)),actions.back(),SLOT(setKind(int)));
      connect(this,SIGNAL(numberChanged(int)),actions.back(),SLOT(setNumber(int)));
    }
    for (i=0;i<actions.size();i++)
      toolbar->addAction(actions[i]);
    upAction=new QAction(this);
    downAction=new QAction(this);
    pixmap->paintArrow(1);
    upAction->setIcon(QIcon(*pixmap));
    upAction->setText(tr("&Up"));
    pixmap->paintArrow(-1);
    downAction->setIcon(QIcon(*pixmap));
    downAction->setText(tr("&Down"));
    toolbar->addAction(upAction);
    toolbar->addAction(downAction);
    numberMenu->addAction(upAction);
    numberMenu->addAction(downAction);
    connect(upAction,SIGNAL(triggered(bool)),this,SLOT(increaseNumber(bool)));
    connect(downAction,SIGNAL(triggered(bool)),this,SLOT(decreaseNumber(bool)));
  }
}

void MirasolWidget::unmakeActions()
{
  int i;
  toolbar->removeAction(downAction);
  toolbar->removeAction(upAction);
  numberMenu->removeAction(downAction);
  numberMenu->removeAction(upAction);
  delete downAction;
  delete upAction;
  for (i=0;i<actions.size();i++)
  {
    toolbar->removeAction(actions[i]);
    delete actions[i];
  }
  menuBar()->clear();
  actions.resize(0);
}
