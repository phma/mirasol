#include "pattern.h"
#include "angle.h"

DotList aster(int n)
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
    ret+=cossin(asterAngle)*sqrt(i+0.5);
  }
  return ret;
}
