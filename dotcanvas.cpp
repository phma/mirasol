#include <iostream>
#include "dotcanvas.h"
using namespace std;

DotCanvas::DotCanvas(QWidget *parent):QWidget(parent)
{
  resize(150,100);
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

void DotCanvas::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  painter.setPen(pen);
  painter.setBrush(brush);
  painter.drawEllipse(50,50,10,10);
}
