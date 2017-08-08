/******************************************************/
/*                                                    */
/* pattern.cpp - figurate numbers and patterns        */
/*                                                    */
/******************************************************/
/* Copyright 2017 Pierre Abbat.
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
#include "pattern.h"
#include <set>
#include "angle.h"
#include "random.h"
#define ASTERSCALE 0.64681617664289504
#define FIBOSCALE 1.72014502785246199494
using namespace std;

xy step0(1,0),step60(0.5,M_SQRT_3_4),step120(-0.5,M_SQRT_3_4);
xy step180(-1,0),step240(-0.5,-M_SQRT_3_4),step300(0.5,-M_SQRT_3_4);

DotList asterPattern(int n)
/* Returns an asteraceous pattern. Pattern invented by H. Vogel in 1979
 * and later by me, not knowing of Vogel. This program is named Mirasol
 * for a large member of the family Asteraceae.
 */
{
  static int asterAngle;
  int i;
  DotList ret;
  for (i=0;i<n;i++)
  {
    asterAngle+=PHITURN;
    ret+=cossin(asterAngle)*sqrt(i+0.5)*ASTERSCALE;
  }
  return ret;
}

DotList productPattern(vector<int> ns)
{
  int i;
  DotList ret(xy(0,0));
  for (i=0;i<ns.size();i++)
    ret=ret*asterPattern(ns[i]);
  return ret;
}

DotList basePattern(int n,int base)
/* base should be less than 256. If base<2 or base>=n, returns asterPattern(n).
 * Otherwise, returns a depicton of n in base, e.g. if n=321 and base=10,
 * returns 300 dots arranged as three hundreds, each composed of ten tens,
 * 20 dots arranged in two tens, and one more dot.
 * 
 * Bases 2 and 3 produce illegible or invisible patterns of 1023 dots. Base 4
 * is barely readable.
 */
{
  int power;
  DotList ret;
  vector<int> baseRep;
  if (base<2 || base>=n)
    ret=asterPattern(n);
  else
  {
    power=1;
    while (power<n)
    {
      power*=base;
      baseRep.push_back(base);
    }
    ret=productPattern(baseRep);
    ret.resize(n);
  }
  return ret;
}

DotList compositePattern(int n)
{
  set<int> factors;
  vector<int> properFactors,twoFactors;
  set<int>::iterator j;
  int i;
  for (i=1;i*i<=n;i++)
    if (n%i==0)
    {
      factors.insert(i);
      factors.insert(n/i);
    }
  for (j=factors.begin();j!=factors.end();++j)
    if (*j>1 && *j<n)
      properFactors.push_back(*j);
  if (properFactors.size())
  {
    twoFactors.push_back(properFactors[rng.uirandom()%properFactors.size()]);
    twoFactors.push_back(n/twoFactors[0]);
  }
  else
    twoFactors.push_back(n);
  return productPattern(twoFactors);
}

DotList fibonacciPattern(int n,xy a,xy c,bool side)
/* The altitude of a Kepler triangle divides the triangle's area in the
 * golden ratio. This function splits n in the golden ratio, splits
 * the triangle in the golden ratio, and recurses, producing a pattern
 * of dots along a space-filling fractal in the Kepler triangle.
 */
{
  xy b,alt;
  DotList ret;
  int bigPart,littlePart;
  alt=turn90(c-a)*M_SQRTCUBE_1PHI;
  if (side)
    alt=-alt;
  b=(c+M_1PHI*a)*M_1PHI+alt;
  if (n>1)
  {
    bigPart=rint(n*M_1PHI);
    littlePart=n-bigPart;
    ret=fibonacciPattern(bigPart,a,b,!side)+fibonacciPattern(littlePart,b,c,!side);
  }
  else if (n==1)
    ret+=(a*15+b*24+c*20)/59;
  return ret;
}

DotList fibonacciPattern(int n)
{
  xy a(sqrt(n)*M_1PHI*FIBOSCALE,-sqrt(n)*M_SQRTCUBE_1PHI*FIBOSCALE);
  return fibonacciPattern(n,a,-a,false);
}

DotList squarePronicPattern(int n)
/* This is used for both square and pronic numbers. It finds the factor
 * closest to the square root, then draws a rectangle with that many dots
 * on the short side. If given a prime like 8191, it produces a long,
 * thin red line.
 */
{
  int i,j,littleDiv,bigDiv;
  DotList ret;
  for (littleDiv=floor(sqrt(n));n>0 && n%littleDiv;--littleDiv);
  if (littleDiv)
    bigDiv=n/littleDiv;
  else
    bigDiv=1; // doesn't matter, 0 is both square and pronic
  for (i=0;i<littleDiv;i++)
    for (j=0;j<bigDiv;j++)
      ret+=xy((2*j+1-bigDiv)/2.,(2*i+1-littleDiv)/2.);
  return ret;
}

DotList trianglePattern(int n)
{
  int i,j;
  double startY;
  DotList ret;
  startY=(sqrt(8*n+1)-3)/2*M_SQRT_1_3;
  for (i=0;(i)*(i+1)/2<=n;i++)
    for (j=0;j<=i && (i)*(i+1)/2+j<n;j++)
      ret+=xy(j-i/2.,startY-i*M_SQRT_3_4);
  return ret;
}

DotList hexagonPattern(int n)
{
  int i;
  xy pos,step(step0);
  DotList ret;
  for (i=0;i<n;i++)
  {
    ret+=pos;
    pos+=step;
    if (pos.getx()>0 && fabs(pos.gety())<0.1)
      step=step120;
    if (pos.getx()>0 && fabs(pos.gety()-M_SQRT_3*pos.getx())<0.1)
      step=step180;
    if (pos.getx()<0 && fabs(pos.gety()+M_SQRT_3*pos.getx())<0.1)
      step=step240;
    if (pos.getx()<0 && fabs(pos.gety())<0.1)
      step=step300;
    if (pos.getx()<0 && fabs(pos.gety()-M_SQRT_3*pos.getx())<0.1)
      step=step0;
    if (pos.getx()>1 && fabs(pos.gety()+M_SQRT_3*(pos.getx()-1))<0.1)
      step=step60;
  }
  return ret;
}

DotList smooth5Pattern(int n)
{
  int i;
  DotList ret;
  vector<int> factors;
  for (i=2;n>1;i++)
    if (n%i==0)
    {
      factors.push_back(1);
      while (n%i==0)
      {
        factors.back()*=i;
        n/=i;
      }
    }
  if (n)
    ret=productPattern(factors);
  return ret;
}

bool isComposite(int n)
{
  int littleDiv;
  for (littleDiv=floor(sqrt(n));n>0 && n%littleDiv;--littleDiv);
  return littleDiv>1;
}

bool isPrime(int n)
{
  int littleDiv;
  for (littleDiv=floor(sqrt(n));n>0 && n%littleDiv;--littleDiv);
  return littleDiv==1 && n>1;
}

bool isFibonacci(int n)
{
  int a,b;
  for (a=0,b=1;a<n;a+=b,b=a-b);
  return a==n;
}

bool isSquare(int n)
{
  int littleDiv,bigDiv;
  for (littleDiv=floor(sqrt(n));n>0 && n%littleDiv;--littleDiv);
  if (littleDiv)
    bigDiv=n/littleDiv;
  else
    bigDiv=0;
  return littleDiv==bigDiv;
}

bool isPronic(int n)
{
  int littleDiv,bigDiv;
  for (littleDiv=floor(sqrt(n));n>0 && n%littleDiv;--littleDiv);
  if (littleDiv)
    bigDiv=n/littleDiv;
  else
    bigDiv=1;
  return littleDiv==bigDiv-1;
}

bool isTriangle(int n)
{
  return isPronic(2*n);
}

bool isHexagon(int n)
{
  return n%6==1 && isPronic(n/3);
}

bool isSmooth5(int n)
{
  if (n==0)
    n=7; // 0 is not smooth, as it is divisible by all primes.
  while ((n%2)==0)
    n/=2;
  while ((n%3)==0)
    n/=3;
  while ((n%5)==0)
    n/=5;
  return n==1;
}

DotList kindPattern(int n,int kind)
{
  switch (kind)
  {
    case KIND_COMPOSITE:
      return compositePattern(n);
      break;
    case KIND_FIBONACCI:
      return fibonacciPattern(n);
      break;
    case KIND_SQUARE:
    case KIND_PRONIC:
      return squarePronicPattern(n);
      break;
    case KIND_TRIANGLE:
      return trianglePattern(n);
      break;
    case KIND_HEXAGON:
      return hexagonPattern(n);
      break;
    case KIND_SMOOTH5:
      return smooth5Pattern(n);
      break;
    default:
      return basePattern(n,kind);
  }
}

bool isKind(int n,int kind)
{
  switch (kind)
  {
    case KIND_COMPOSITE:
      return isComposite(n);
      break;
    case KIND_PRIME:
      return isPrime(n);
      break;
    case KIND_FIBONACCI:
      return isFibonacci(n);
      break;
    case KIND_SQUARE:
      return isSquare(n);
      break;
    case KIND_PRONIC:
      return isPronic(n);
      break;
    case KIND_TRIANGLE:
      return isTriangle(n);
      break;
    case KIND_HEXAGON:
      return isHexagon(n);
      break;
    case KIND_SMOOTH5:
      return isSmooth5(n);
      break;
    default:
      return true;
  }
}
