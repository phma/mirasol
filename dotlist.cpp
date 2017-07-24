#include "dotlist.h"
#include <cstring>
using namespace std;

DotList::DotList()
{
  list.clear();
}

DotList::DotList(xy dot)
{
  list.push_back(dot);
}

xy DotList::operator[](int n)
{
  return list[n];
}

int DotList::size() const
{
  return list.size();
}

/* Addition of dotlists is commutative as far as the set of dots goes,
 * but not their order. Multiplication of dotlists is commutative as far
 * as the number of dots goes, but not the set.
 */
DotList operator+(const DotList l,const DotList r)
{
  DotList ret;
  ret.list=l.list;
  ret.list.resize(l.size()+r.size());
  memmove(&ret.list[l.size()],&r.list[0],r.size()*sizeof(xy));
  return ret;
}

DotList operator+(const DotList l,const xy r)
{
  DotList ret;
  ret.list=l.list;
  ret.list.push_back(r);
  return ret;
}

DotList operator+=(DotList &l,const xy r)
{
  l.list.push_back(r);
  return l;
}

DotList operator*(const DotList l,const DotList r)
// Returns l.size() copies of r arranged in l enlarged by the radius of r.
{
  int i,j,lsz,rsz;
  double scale;
  DotList ret;
  lsz=l.size();
  rsz=r.size();
  ret.list.resize(lsz*rsz);
  for (scale=j=0;j<rsz;j++)
    if (r.list[j].length()>scale)
      scale=r.list[j].length();
  scale+=0.5; // add the radius of a dot
  for (i=0;i<lsz;i++)
    for (j=0;j<rsz;j++)
      ret.list[i*rsz+j]=l.list[i]*scale+r.list[i];
  return ret;
}
