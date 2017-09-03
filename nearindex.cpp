/******************************************************/
/*                                                    */
/* nearindex.cpp - nearness map from xy to int        */
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
#include "nearindex.h"
#include <cmath>
using namespace std;

XyIndex::XyIndex()
{
  x=y=0;
}

XyIndex::XyIndex(int X,int Y)
{
  x=X;
  y=Y;
}

bool operator<(const XyIndex &l,const XyIndex &r)
// This is only so that the map has a comparison operator.
{
  if (l.y!=r.y)
    return l.y<r.y;
  else
    return l.x<r.x;
}

XyIndex operator+(const XyIndex &l,const XyIndex &r)
{
  return XyIndex(l.x+r.x,l.y+r.y);
}

XyInt::XyInt()
{
  loc=xy(0,0);
  num=0;
}

XyInt::XyInt(xy Loc,int Num)
{
  loc=Loc;
  num=Num;
}

void NearIndex::clear()
{
  lattice.clear();
}

int& NearIndex::operator[](xy inx)
{
  int i;
  XyIndex linx(floor(inx.getx()/SQSIZE),floor(inx.gety()/SQSIZE));
  vector<XyInt>& bucket=lattice[linx];
  for (i=0;i<bucket.size() && bucket[i].loc!=inx;i++);
  if (i>=bucket.size())
    bucket.push_back(XyInt(inx,0));
  return bucket[i].num;
}

vector<xy> NearIndex::within(xy center,double radius,bool includeCenter)
{
  int xofs,yofs,i;
  double dst;
  XyIndex ctr(floor(center.getx()/SQSIZE),floor(center.gety()/SQSIZE));
  vector<XyInt> *bucket;
  vector<xy> ret;
  int iradius=ceil(radius/SQSIZE+1.415);
  for (yofs=-iradius;yofs<=iradius;yofs++)
    for (xofs=-iradius;xofs<=iradius;xofs++)
    {
      bucket=&lattice[ctr+XyIndex(xofs,yofs)];
      for (i=0;i<bucket->size();i++)
      {
        dst=dist((*bucket)[i].loc,center);
        if (dst<=radius && (dst>0 || includeCenter))
          ret.push_back((*bucket)[i].loc);
      }
    }
  return ret;
}
