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
