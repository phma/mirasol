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
#include <iostream>
#include "angle.h"

using namespace std;

int splitAngle;

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
  int nstartpoints,i,angerr,samecount,endangle;
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
    //cout<<stdist.size()<<" +"<<inserenda.size()<<" -"<<delenda.size()<<endl;
    if (lastclosedist>closedist)
      samecount=0;
    else
      samecount++;
  } while (samecount<7 && stdist.size()<1000 && (stdist.size()<13 || closedist<2));
  //cout<<"samecount "<<samecount<<" stdist "<<stdist.size()<<endl;
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
  start=QDateTime::currentDateTimeUtc().time();
  duration=0;
}

MultiTrajectory::MultiTrajectory(DotList startList,int startAngle,DotList endList,int endAngle)
/* Constructs a MultiTrajectory taking dots in startList by straight lines
 * to dots in endList. If startAngle and endAngle are equal, the total length
 * of all the trajectories is close to minimum. If one of the DotLists is
 * bigger (which it isn't), some of the dots are discarded, but which ones
 * depends on the angle.
 */
{
  if (startList.size()<2 || endList.size()<2)
  {
    if (startList.size()>0 && endList.size()>0)
      traj.push_back(Trajectory(startList[0],endList[0]));
    start=QDateTime::currentDateTimeUtc().time();
    duration=0;
  }
  else
  {
    xy startDir=cossin(startAngle),endDir=cossin(endAngle);
    multimap<double,xy> startOrder,endOrder;
    int i;
    multimap<double,xy>::iterator oi;
    DotList startFirst,startLast,endFirst,endLast;
    for (i=0;i<startList.size();i++)
      startOrder.insert(pair<double,xy>(dot(startDir,startList[i]),startList[i]));
    for (i=0;i<endList.size();i++)
      endOrder.insert(pair<double,xy>(dot(endDir,endList[i]),endList[i]));
    for (oi=startOrder.begin();oi!=startOrder.end();oi++)
      if (startFirst.size()*2<startList.size())
        startFirst+=(oi->second);
      else
        startLast+=(oi->second);
    for (oi=endOrder.begin();oi!=endOrder.end();oi++)
      if (endFirst.size()*2<endList.size())
        endFirst+=(oi->second);
      else
        endLast+=(oi->second);
    MultiTrajectory firstHalf(startFirst,startAngle+PHI2TURN,endFirst,endAngle+PHI2TURN);
    MultiTrajectory lastHalf(startLast,startAngle+PHI2TURN,endLast,endAngle+PHI2TURN);
    // PHI2TURN is 445°, just over 5° shy of a right angle, but it's irrational.
    for (i=0;i<firstHalf.traj.size();i++)
      traj.push_back(firstHalf.traj[i]);
    for (i=0;i<lastHalf.traj.size();i++)
      traj.push_back(lastHalf.traj[i]);
    start=firstHalf.start;
    duration=start.msecsTo(lastHalf.start)+lastHalf.duration;
    if (duration<0)
      duration+=86400000;
  }
}

MultiTrajectory::MultiTrajectory(DotList startList,int twistAngle,DotList endList):
  MultiTrajectory(startList,splitAngle,endList,splitAngle+twistAngle)
{
  splitAngle+=PHITURN;
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

void MultiTrajectory::setKind(int Kind)
{
  kind=Kind;
}

QTime MultiTrajectory::getStartTime()
{
  return start;
}

QTime MultiTrajectory::getEndTime()
{
  return start.addMSecs(duration);
}

int MultiTrajectory::getKind()
{
  return kind;
}
