#include "xy.h"

class Trajectory
{
public:
  Trajectory();
  Trajectory(xy pos0,xy pos1);
  void push(xy adj);
  xy position(double t);
  double closest();
  friend Trajectory operator+(const Trajectory &l,const Trajectory &r);
  friend Trajectory operator-(const Trajectory &l,const Trajectory &r);
private:
  xy start,ctrl,end;
};
