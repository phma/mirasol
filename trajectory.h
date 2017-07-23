#include "xy.h"

class Trajectory
/* Represents the motion of a dot from initial position to final position.
 * The program adjusts the trajectories so that dots do not collide as they move.
 * Trajectories are quadratic splines.
 */
{
public:
  Trajectory();
  Trajectory(xy pos0,xy pos1);
  void push(xy adj);
  xy position(double t);
  double closest(); // Time of closest approach. Done on difference.
  friend Trajectory operator+(const Trajectory &l,const Trajectory &r);
  friend Trajectory operator-(const Trajectory &l,const Trajectory &r);
private:
  xy start,ctrl,end;
};
