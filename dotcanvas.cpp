#include <iostream>
#include "dotcanvas.h"
using namespace std;

DotCanvas::DotCanvas(QWidget *parent):QWidget(parent)
{
  resize(150,100);
  setAutoFillBackground(true);
  setBackgroundRole(QPalette::Base);
  show();
}
