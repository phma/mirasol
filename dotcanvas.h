#ifndef DOTCANVAS_H
#define DOTCANVAS_H
#include <QtWidgets>
#include <QPixmap>
#include <vector>
#include "xy.h"
#include "dotlist.h"

class DotCanvas: public QWidget
{
  Q_OBJECT
public:
  DotCanvas(QWidget *parent=0);
  void setPen(const QPen &qpen);
  void setBrush(const QBrush &qbrush);
  void setDots(DotList newDots);
  void setSize();
public slots:
protected:
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
private:
  QPen pen;
  QBrush brush;
  DotList dots;
  xy center; // of widget
  xy middle; // of rectangle containing dots
  double scale;
  double top,left,bottom,right; // These are 0, not infinity, if dots is empty.
};

class DotPixmap: public QPixmap
{
public:
  DotPixmap(int width,int height);
  void setPen(const QPen &qpen);
  void setBrush(const QBrush &qbrush);
  void setDots(DotList newDots);
  void setSize();
  void paintDots();
private:
  QPen pen;
  QBrush brush;
  DotList dots;
  xy center; // of widget
  xy middle; // of rectangle containing dots
  double scale;
  double top,left,bottom,right; // These are 0, not infinity, if dots is empty.
};
#endif
