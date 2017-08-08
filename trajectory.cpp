/******************************************************/
/*                                                    */
/* trajectory.cpp - quadratic trajectories            */
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
#include "trajectory.h"
#include <map>
#include <set>
#include "angle.h"

using namespace std;

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
  int nstartpoints,i,angerr,angtoler,endangle;
  double closest,closedist,lastclosedist,fardist,len2,vertex;
  map<double,double> stdist;
  set<double> inserenda,delenda;
  set<double>::iterator j;
  map<double,double>::iterator k0,k1,k2;
  nstartpoints=4;
  closedist=INFINITY;
  fardist=0;
  for (i=0;i<=nstartpoints;i++)
    inserenda.insert((double)i/nstartpoints);
  do
  {
    lastclosedist=closedist;
    for (j=delenda.begin();j!=delenda.end();++j)
      stdist.erase(*j);
    for (j=inserenda.begin();j!=inserenda.end();++j)
    {
      len2=sqr(position(*j).length());
      if (len2<closedist)
      {
	closest=*j;
	closedist=len2;
	//angerr=((bearing(*j)-atan2i((xy)station(*j)-topoint))&(DEG180-1))-DEG90;
      }
      if (len2>fardist)
	fardist=len2;
      stdist[*j]=len2;
    }
    inserenda.clear();
    delenda.clear();
    for (k0=k1=stdist.begin(),k2=++k1,++k2;stdist.size()>2 && k2!=stdist.end();++k0,++k1,++k2)
    {
      vertex=minquad(k0->first,k0->second,k1->first,k1->second,k2->first,k2->second);
      if (vertex<0 && vertex>-0.5)
	vertex=-vertex;
      if (vertex>1 && vertex<1.5)
	vertex=2-vertex;
      if (stdist.count(vertex) && vertex!=k1->first)
	delenda.insert(k1->first);
      if (!stdist.count(vertex) && vertex>=0 && vertex<=1)
	inserenda.insert(vertex);
    }
    if (lastclosedist>closedist)
      angtoler=1;
    else
      angtoler*=7;
  } while (16777216>=angtoler);
  return closest;
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

MultiTrajectory::MultiTrajectory()
{
  start.currentTime();
  duration=0;
}

int MultiTrajectory::timeSinceStart(QTime t)
{
  int interval=start.msecsTo(t);
  if (interval<-43200000)
    interval+=86400000;
  if (interval>43200000)
    interval-=86400000;
  return interval;
}

int MultiTrajectory::foreAft(QTime t)
{
  int interval=timeSinceStart(t);
  return (interval>duration)-(interval<0);
}

DotList MultiTrajectory::atTime(QTime t)
{
  int interval=timeSinceStart(t);
  int i;
  double progress=(double)interval/duration;
  DotList ret;
  if (progress<0)
    progress=0;
  if (progress>1)
    progress=1;
  for (i=0;i<traj.size();i++)
    ret+=traj[i].position(progress);
  return ret;
}

void MultiTrajectory::setTime(QTime Start,int Duration)
{
  start=Start;
  duration=Duration;
}

void MultiTrajectory::setTraj(std::vector<Trajectory> Traj)
{
  traj=Traj;
}
