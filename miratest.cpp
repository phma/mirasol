/******************************************************/
/*                                                    */
/* miratest.cpp - test program                        */
/*                                                    */
/******************************************************/
/* Copyright 2016,2017 Pierre Abbat.
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
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include "trajectory.h"
#include "dotlist.h"
#include "pattern.h"
using namespace std;

void testTrajectory()
{
  Trajectory tra0(xy(2,3),xy(8,4)),tra1(xy(5,8),xy(16,8)),tra2;
  xy p0,p1;
  tra2=tra0+tra1; // (7,11)->(24,12)
  p0=tra2.position(0.75);
  cout<<p0.getx()<<' '<<p0.gety()<<endl;
  assert(p0==xy(19.75,11.75));
}

double shortestDistance(DotList a)
{
  int i,j;
  double distance=INFINITY;
  for (i=0;i<a.size();i++)
    for (j=0;j<i;j++)
      if (dist(a[i],a[j])<distance)
        distance=dist(a[i],a[j]);
  return distance;
}

void testAster()
{
  DotList a;
  double distance;
  a=asterPattern(1000);
  distance=shortestDistance(a);
  cout<<"Shortest distance aster "<<distance<<endl;
  assert(fabs(distance-1)<1e-12);
}

void testFibonacci()
{
  DotList a;
  double distance;
  a=fibonacciPattern(987);
  distance=shortestDistance(a);
  cout<<"Shortest distance fibo "<<distance<<endl;
  assert(fabs(distance-1)<1e-12);
}

int main(int argc, char *argv[])
{
  testTrajectory();
  testAster();
  testFibonacci();
  return 0;
}
