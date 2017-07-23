#include "trajectory.h"

double minquad(double x0,double y0,double x1,double y1,double x2,double y2)
/* Finds the minimum (or maximum) of a quadratic, given three points on it.
 * x1 should be between x0 and x2.
 * Used to find the closest point on a trajectory to the origin.
 */
{
  double xm,s1,s2;
  xm=(x0+2*x1+x2)/4;
  s1=(y1-y0)/(x1-x0);
  s2=(y2-y1)/(x2-x1);
  //cout<<"s1="<<s1<<" s2="<<s2<<" xm="<<xm<<endl;
  return xm+(x2-x0)*(s1+s2)/(s1-s2)/4;
}

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
// Returns the position at time t, which ranges from 0 to 1.
{
  return t*t*end+2*t*(1-t)*ctrl+(1-t)*(1-t)*start;
}

double Trajectory::closest()
/* Returns the time, from 0 to 1, when the trajectory is closest to (0,0).
 * Since the trajectory is quadratic, this requires minimizing a quartic.
 * This is done by parabolic interpolation. To find when two trajectories
 * are closest to each other, do this to their difference.
 */
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
