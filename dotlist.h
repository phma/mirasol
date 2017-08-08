/******************************************************/
/*                                                    */
/* dotlist.h - list of dot positions                  */
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
#ifndef DOTLIST_H
#define DOTLIST_H
#include <vector>
#include "xy.h"

class DotList
{
public:
  DotList();
  DotList(xy dot);
  xy operator[](int n);
  int size() const;
  void resize(unsigned int n);
  friend DotList operator+(const DotList l,const DotList r);
  friend DotList operator+(const DotList l,const xy r);
  friend DotList operator+=(DotList &l,const xy r);
  friend DotList operator*(const DotList l,const DotList r);
private:
  std::vector<xy> list;
};
#endif
