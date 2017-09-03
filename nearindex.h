/******************************************************/
/*                                                    */
/* nearindex.h - nearness map from xy to int          */
/*                                                    */
/******************************************************/
/* Copyright 2017 Pierre Abbat.
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
#include <map>
#include <vector>
#include "xy.h"
#define SQSIZE 2

class XyIndex
{
public:
  XyIndex();
  XyIndex(int X,int Y);
  friend bool operator<(const XyIndex &l,const XyIndex &r);
  friend XyIndex operator+(const XyIndex &l,const XyIndex &r);
private:
  int x,y;
};

struct XyInt
{
  XyInt();
  XyInt(xy Loc,int Num);
  xy loc;
  int num;
};

class NearIndex
{
public:
  void clear();
  int& operator[](xy inx);
  std::vector<xy> within(xy center,double radius,bool includeCenter);
private:
  std::map<XyIndex,std::vector<XyInt> > lattice;
};
