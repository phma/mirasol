/******************************************************/
/*                                                    */
/* dotcanvas.h - widget and pixmap for dots           */
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
  void paintArrow(int dir);
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
