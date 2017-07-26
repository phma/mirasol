#include "pattern.h"
#include "angle.h"
#define ASTERSCALE 0.64681617664289504
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

    