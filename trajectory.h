#include <QTime>
#include "xy.h"
#include "dotlist.h"

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

class MultiTrajectory
{
public:
  int foreAft(QTime t); // -1 if t is before, 0 if during, 1 if after
  DotList atTime(QTime t);
  void setTime(QTime Start,int Duration);
  void setTraj(std::vector<Trajectory> Traj);
private:
  QTime start;
  int duration;
  std::vector<Trajectory> traj;
  int timeSinceStart(QTime t);
};

