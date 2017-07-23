#include <cmath>
#include <cstdlib>
#include "xy.h"
#include "angle.h"

xy::xy(double e,double n)
{x=e;
 y=n;
 }

xy::xy()
{x=0;
 y=0;
 }

double xy::getx() const
{
  return x;
}

double xy::gety() const
{
  return y;
}

double xy::length() const
{
  return hypot(x,y);
}

bool xy::isfinite() const
{
  return std::isfinite(x) && std::isfinite(y);
}

bool xy::isnan() const
{
  return std::isnan(x) || std::isnan(y);
}

xy xy::conj() const
{
  return xy(x,-y);
}

void xy::_roscat(xy tfrom,int ro,double sca,xy cis,xy tto)
{
  double tx,ty;
  x-=tfrom.x;
  y-=tfrom.y;
  tx=x*cis.x-y*cis.y;
  ty=y*cis.x+x*cis.y;
  x=tx+tto.x;
  y=ty+tto.y;
}

void xy::roscat(xy tfrom,int ro,double sca,xy tto)
{
  _roscat(tfrom,ro,sca,cossin(ro)*sca,tto);
}

xy operator+(const xy &l,const xy &r)
{xy sum(l.x+r.x,l.y+r.y);
 return sum;
 }

xy operator+=(xy &l,const xy &r)
{
  l.x+=r.x;
  l.y+=r.y;
  return l;
}

xy operator*(double l,const xy &r)
{
  xy prod(l*r.x,l*r.y);
  return prod;
}

xy operator*(const xy &l,double r)
{
  xy prod(l.x*r,l.y*r);
  return prod;
}

xy operator-(const xy &l,const xy &r)
{
  xy sum(l.x-r.x,l.y-r.y);
  return sum;
}

xy operator-(const xy &r)
{
  xy sum(-r.x,-r.y);
  return sum;
}

xy operator/(const xy &l,double r)
{xy prod(l.x/r,l.y/r);
 return prod;
 }

xy operator/=(xy &l,double r)
{
  l.x/=r;
  l.y/=r;
  return l;
}

bool operator!=(const xy &l,const xy &r)
{
  return l.x!=r.x || l.y!=r.y;
}

bool operator==(const xy &l,const xy &r)
{
  return l.x==r.x && l.y==r.y;
}

xy turn90(xy a)
{
  return xy(-a.y,a.x);
}

xy turn(xy a,int angle)
{
  double s,c;
  s=sin(angle);
  c=cos(angle);
  return xy(c*a.x-s*a.y,s*a.x+c*a.y);
}

double dist(xy a,xy b)
{return hypot(a.x-b.x,a.y-b.y);
 }

int dir(xy a,xy b)
{return atan2i(b-a);
 }

double dot(xy a,xy b)
{return (a.y*b.y+a.x*b.x);
 }
