/******************************************************/
/*                                                    */
/* dotcanvas.cpp - widget and pixmap for dots         */
/*                                                    */
/******************************************************/
/* Copyright 2015,2016,2017 Pierre Abbat.
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
#include "dotcanvas.h"
using namespace std;
#define DOTRADIUS 0.45

DotCanvas::DotCanvas(QWidget *parent):QWidget(parent)
{
  setAutoFillBackground(true);
  setBackgroundRole(QPalette::Base);
  setBrush(Qt::red);
  setPen(Qt::NoPen);
  show();
}

void DotCanvas::setPen(const QPen &qpen)
{
  pen=qpen;
}

void DotCanvas::setBrush(const QBrush &qbrush)
{
  brush=qbrush;
}

void DotCanvas::setSize()
{
  double xscale,yscale;
  center=xy(width(),height())/2.;
  xscale=width()/(right-left+1);
  yscale=height()/(top-bottom+1);
  if (xscale<yscale)
    scale=xscale;
  else
    scale=yscale;
  middle=xy(right+left,top+bottom)/2;
  //cout<<"center "<<center<<" scale "<<scale<<endl;
}

void DotCanvas::setDots(DotList newDots)
{
  dots=newDots;
  int i;
  top=left=bottom=right=0;
  for (i=0;i<dots.size();i++)
  {
    if (dots[i].gety()>top)
      top=dots[i].gety();
    if (dots[i].getx()<left)
      left=dots[i].getx();
    if (dots[i].gety()<bottom)
      bottom=dots[i].gety();
    if (dots[i].getx()>right)
      right=dots[i].getx();
  }
  setSize();
  update();
}

void DotCanvas::paintEvent(QPaintEvent *event)
{
  int i;
  xy canvasdot;
  QPainter painter(this);
  painter.setPen(pen);
  painter.setBrush(brush);
  painter.setRenderHint(QPainter::Antialiasing,true);
  for (i=0;i<dots.size();i++)
  {
    canvasdot=(dots[i]-middle).conj()*scale+center; // conj because canvas is y-downward
    painter.drawEllipse(QPointF(canvasdot.getx(),canvasdot.gety()),DOTRADIUS*scale,DOTRADIUS*scale);
  }
}

void DotCanvas::resizeEvent(QResizeEvent *event)
{
  setSize();
  QWidget::resizeEvent(event);
}

DotPixmap::DotPixmap(int width,int height):QPixmap(width,height)
{
  setBrush(Qt::red);
  setPen(Qt::NoPen);
}

void DotPixmap::setPen(const QPen &qpen)
{
  pen=qpen;
}

void DotPixmap::setBrush(const QBrush &qbrush)
{
  brush=qbrush;
}

void DotPixmap::setSize()
{
  double xscale,yscale;
  center=xy(width(),height())/2.;
  xscale=width()/(right-left+1);
  yscale=height()/(top-bottom+1);
  if (xscale<yscale)
    scale=xscale;
  else
    scale=yscale;
  middle=xy(right+left,top+bottom)/2;
}

void DotPixmap::setDots(DotList newDots)
{
  dots=newDots;
  int i;
  top=left=bottom=right=0;
  for (i=0;i<dots.size();i++)
  {
    if (dots[i].gety()>top)
      top=dots[i].gety();
    if (dots[i].getx()<left)
      left=dots[i].getx();
    if (dots[i].gety()<bottom)
      bottom=dots[i].gety();
    if (dots[i].getx()>right)
      right=dots[i].getx();
  }
  setSize();
}

void DotPixmap::paintDots()
{
  int i;
  xy canvasdot;
  QPainter painter(this);
  fill();
  painter.setPen(pen);
  painter.setBrush(brush);
  painter.setRenderHint(QPainter::Antialiasing,true);
  for (i=0;i<dots.size();i++)
  {
    canvasdot=(dots[i]-middle).conj()*scale+center; // conj because canvas is y-downward
    painter.drawEllipse(QPointF(canvasdot.getx(),canvasdot.gety()),DOTRADIUS*scale,DOTRADIUS*scale);
  }
}

void DotPixmap::paintArrow(int dir)
{
  QPainter painter(this);
  QPolygonF polygon;
  fill();
  painter.setPen(pen);
  painter.setBrush(Qt::blue);
  painter.setRenderHint(QPainter::Antialiasing,true);
  polygon<<QPointF(width()/2.-dir*width()*0.4,height()/2.+dir*height()*0.1)
         <<QPointF(width()/2.                ,height()/2.-dir*height()*0.2)
         <<QPointF(width()/2.+dir*width()*0.4,height()/2.+dir*height()*0.1);
  painter.drawConvexPolygon(polygon);
}
