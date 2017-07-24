#include <vector>
#include "xy.h"

class DotList
{
public:
  DotList();
  DotList(xy dot);
  xy operator[](int n);
  int size() const;
  friend DotList operator+(const DotList l,const DotList r);
  friend DotList operator+(const DotList l,const xy r);
  friend DotList operator+=(DotList &l,const xy r);
  friend DotList operator*(const DotList l,const DotList r);
private:
  std::vector<xy> list;
};
