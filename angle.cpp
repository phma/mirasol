/******************************************************/
/*                                                    */
/* angle.cpp - angles as binary fractions of rotation */
/*                                                    */
/******************************************************/
/* Copyright 2016 Pierre Abbat.
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

#include <cstring>
#include <cstdio>
#include "angle.h"

double sqr(double x)
{
  return x*x;
}

double sin(int angle)
{return sinl(angle*M_PIl/1073741824.);
 }

double cos(int angle)
{return cosl(angle*M_PIl/1073741824.);
 }

double sinhalf(int angle)
{return sinl(angle*M_PIl/2147483648.);
 }

double coshalf(int angle)
{return cosl(angle*M_PIl/2147483648.);
 }

double tanhalf(int angle)
{return tanl(angle*M_PIl/2147483648.);
 }

double cosquarter(int angle)
{return cosl(angle*M_PIl/4294967296.);
 }

double tanquarter(int angle)
{return tanl(angle*M_PIl/4294967296.);
 }

int atan2i(double y,double x)
{return rint(atan2(y,x)/M_PIl*1073741824.);
 }

int atan2i(xy vect)
{
  return atan2i(vect.gety(),vect.getx());
}

xy cossin(double angle)
{
  return xy(cos(angle),sin(angle));
}

xy cossin(int angle)
{
  return xy(cos(angle),sin(angle));
}

xy cossinhalf(int angle)
{
  return xy(coshalf(angle),sinhalf(angle));
}

int foldangle(int angle)
{
  if (((unsigned)angle>>30)%3)
    angle^=0x80000000;
  return angle;
}

bool isinsector(int angle,int sectors)
/* Quick check for ranges of angles. angle is in [0°,720°), so sectors
 * is normally an unsigned multiple of 65537. Bit 0 is [0,22.5°), bit 1
 * is [22.5°,45°), etc.
 */
{
  return ((sectors>>((unsigned)angle>>27))&1);
}

double bintorot(int angle)
{
  return angle/2147483648.;
}

double bintogon(int angle)
{
  return bintorot(angle)*400;
}

double bintodeg(int angle)
{
  return bintorot(angle)*360;
}

double bintomin(int angle)
{
  return bintorot(angle)*21600;
}

double bintosec(int angle)
{
  return bintorot(angle)*1296000;
}

double bintorad(int angle)
{
  return bintorot(angle)*M_PIl*2;
}

int rottobin(double angle)
{
  double iprt=0,fprt;
  fprt=2*modf(angle/2,&iprt);
  if (fprt>=1)
    fprt-=2;
  if (fprt<-1)
    fprt+=2;
  return lrint(2147483648.*fprt);
}

int degtobin(double angle)
{
  return rottobin(angle/360);
}

int mintobin(double angle)
{
  return rottobin(angle/21600);
}

int sectobin(double angle)
{
  return rottobin(angle/1296000);
}

int gontobin(double angle)
{
  return rottobin(angle/400);
}

int radtobin(double angle)
{
  return rottobin(angle/M_PIl/2);
}

