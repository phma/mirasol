/******************************************************/
/*                                                    */
/* trajectory.h - quadratic trajectories              */
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
#include <QTime>
#include "xy.h"
#include "dotlist.h"
#define NTIMES 5

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
  xy displacement();
  friend Trajectory operator+(const Trajectory &l,const Trajectory &r);
  friend Trajectory operator-(const Trajectory &l,const Trajectory &r);
private:
  xy start,ctrl,end;
};

class MultiTrajectory
{
public:
  MultiTrajectory();
  MultiTrajectory(DotList startList,int twistAngle,DotList endList);
  int foreAft(QTime t); // -1 if t is before, 0 if during, 1 if after
  DotList atTime(QTime t);
  void setTime(QTime Start,int Duration);
  void setTraj(std::vector<Trajectory> Traj);
  void setKind(int Kind);
  QTime getStartTime();
  QTime getEndTime();
  int getKind();
  void bendAvoid();
private:
  QTime start;
  int duration;
  int kind;
  std::vector<Trajectory> traj;
  MultiTrajectory(DotList startList,int startAngle,DotList endList,int endAngle);
  int timeSinceStart(QTime t);
};
