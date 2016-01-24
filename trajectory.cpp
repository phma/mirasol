#include "trajectory.h"

Trajectory::Trajectory()
{
  start=end=ctrl=xy(0,0);
}

Trajectory::Trajectory(xy pos0,xy pos1)
{
  start=pos0;
  end=pos1;
  ctrl=(pos0+pos1)/2;
}

void Trajectory::push(xy adj)
{
  ctrl+=adj;
}

xy Trajectory::position(double t)
{
  return t*t*end+2*t*(1-t)*ctrl+(1-t)*(1-t)*start;
}

double Trajectory::closest()
{
  //tba
}

Trajectory operator+(const Trajectory &l,const Trajectory &r)
{
  Trajectory ret;
  ret.start=l.start+r.start;
  ret.ctrl=l.ctrl+r.ctrl;
  ret.end=l.end+r.end;
  return ret;
}

Trajectory operator-(const Trajectory &l,const Trajectory &r)
{
  Trajectory ret;
  ret.start=l.start-r.start;
  ret.ctrl=l.ctrl-r.ctrl;
  ret.end=l.end-r.end;
  return ret;
}
