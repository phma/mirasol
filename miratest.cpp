#include <iostream>
#include <cassert>
#include "trajectory.h"
using namespace std;

void testtrajectory()
{
  Trajectory tra0(xy(2,3),xy(8,4)),tra1(xy(5,8),xy(16,8)),tra2;
  xy p0,p1;
  tra2=tra0+tra1; // (7,11)->(24,12)
  p0=tra2.position(0.75);
  cout<<p0.getx()<<' '<<p0.gety()<<endl;
  assert(p0==xy(19.75,11.75));
}

int main(int argc, char *argv[])
{
  testtrajectory();
  return 0;
}
