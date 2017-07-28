#include "pattern.h"
#include <set>
#include "angle.h"
#include "random.h"
#define ASTERSCALE 0.64681617664289504
#define FIBOSCALE 1.72014502785246199494
using namespace std;

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
  for (littleDiv=floor(sqrt(n));n%littleDiv;--littleDiv);
  if (littleDiv)
    bigDiv=n/littleDiv;
  else
    bigDiv=1; // doesn't matter, 0 is both square and pronic
  for (i=0;i<littleDiv;i++)
    for (j=0;j<bigDiv;j++)
      ret+=xy((2*j+1-bigDiv)/2.,(2*i+1-littleDiv)/2.);
  return ret;
}
