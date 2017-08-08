/******************************************************/
/*                                                    */
/* dotlist.cpp - list of dot positions                */
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
#include "dotlist.h"
#include <cstring>
using namespace std;

DotList::DotList()
{
  list.clear();
}

DotList::DotList(xy dot)
{
  list.push_back(dot);
}

xy DotList::operator[](int n)
{
  return list[n];
}

int DotList::size() const
{
  return list.size();
}

void DotList::resize(unsigned int n)
/* Don't resize to bigger than current size. It'll add a lot of dots (0,0),
 * which will all look like one dot.
 */
{
  list.resize(n);
}

/* Addition of dotlists is commutative as far as the set of dots goes,
 * but not their order. Multiplication of dotlists is commutative as far
 * as the number of dots goes, but not the set.
 */
DotList operator+(const DotList l,const DotList r)
{
  DotList ret;
  ret.list=l.list;
  ret.list.resize(l.size()+r.size());
  memmove(&ret.list[l.size()],&r.list[0],r.size()*sizeof(xy));
  return ret;
}

DotList operator+(const DotList l,const xy r)
{
  DotList ret;
  ret.list=l.list;
  ret.list.push_back(r);
  return ret;
}

DotList operator+=(DotList &l,const xy r)
{
  l.list.push_back(r);
  return l;
}

DotList operator*(const DotList l,const DotList r)
// Returns l.size() copies of r arranged in l enlarged by the radius of r.
{
  int i,j,lsz,rsz;
  double scale;
  DotList ret;
  lsz=l.size();
  rsz=r.size();
  ret.list.resize(lsz*rsz);
  for (scale=j=0;j<rsz;j++)
    if (r.list[j].length()>scale)
      scale=r.list[j].length();
  scale=2*scale+1; // add the radius of a dot, and double so that they don't overlap
  for (i=0;i<lsz;i++)
    for (j=0;j<rsz;j++)
      ret.list[i*rsz+j]=l.list[i]*scale+r.list[j];
  return ret;
}
