/******************************************************/
/*                                                    */
/* xy.h - points in xy-plane                          */
/*                                                    */
/******************************************************/
/* Copyright 2016,2017,2021 Pierre Abbat.
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

#ifndef XY_H
#define XY_H
#include <cmath>
class xy
{
public:
  xy(double e,double n);
  xy();
  double getx() const;
  double gety() const;
  double length() const;
  bool isfinite() const;
  bool isnan() const;
  xy conj() const;
  void _roscat(xy tfrom,int ro,double sca,xy cis,xy tto);
  virtual void roscat(xy tfrom,int ro,double sca,xy tto); // rotate, scale, translate
  friend xy operator+(const xy &l,const xy &r);
  friend xy operator+=(xy &l,const xy &r);
  friend xy operator-=(xy &l,const xy &r);
  friend xy operator-(const xy &l,const xy &r);
  friend xy operator-(const xy &r);
  friend xy operator*(const xy &l,double r);
  friend xy operator*(double l,const xy &r);
  friend xy operator/(const xy &l,double r);
  friend xy operator/=(xy &l,double r);
  friend xy operator*=(xy &l,double r);
  friend bool operator!=(const xy &l,const xy &r);
  friend bool operator==(const xy &l,const xy &r);
  friend xy turn90(xy a);
  friend xy turn(xy a,int angle);
  friend double dist(xy a,xy b);
  friend int dir(xy a,xy b);
  friend double dot(xy a,xy b);
  friend double area3(xy a,xy b,xy c);
protected:
  double x,y;
};
#endif
