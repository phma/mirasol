#include <iostream>
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

void testAster()
{
  int i,j;
  double distance=INFINITY;
  DotList a;
  a=asterPattern(1000);
  for (i=0;i<a.size();i++)
    for (j=0;j<i;j++)
      if (dist(a[i],a[j])<distance)
        distance=dist(a[i],a[j]);
  cout<<"Shortest distance "<<distance<<endl;
  assert(fabs(distance-1)<1e-12);
}

int main(int argc, char *argv[])
{
  testTrajectory();
  testAster();
  return 0;
}
