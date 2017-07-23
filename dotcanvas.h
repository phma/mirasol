#ifndef DOTCANVAS_H
#define DOTCANVAS_H
#include <QtWidgets>
#include <vector>
#include "xy.h"

class DotCanvas: public QWidget
{
  Q_OBJECT
public:
  DotCanvas(QWidget *parent=0);
  void setPen(const QPen &qpen);
  void setBrush(const QBrush &qbrush);
  void setDots(std::vector<xy> newDots);
  void setSize();
public slots:
protected:
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
private:
  QPen pen;
  QBrush brush;
  std::vector<xy> dots;
  xy center;
  double scale;
  double top,left,bottom,right; // These are 0, not infinity, if dots is empty.
};
#endif
