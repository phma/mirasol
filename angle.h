/******************************************************/
/*                                                    */
/* angle.h - angles as binary fractions of rotation   */
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
#ifndef ANGLE_H
#define ANGLE_H
#include <cmath>
#include <string>
#include "xy.h"

#ifndef M_PIl
#define M_PIl M_PI
#endif

double sqr(double x);

double sin(int angle);
double cos(int angle);
double sinhalf(int angle);
double coshalf(int angle);
double tanhalf(int angle);
double cosquarter(int angle);
double tanquarter(int angle);
int atan2i(double y,double x);
int atan2i(xy vect); // range is [-536870912,536870912]
xy cossin(double angle);
xy cossin(int angle);
xy cossinhalf(int angle);

int foldangle(int angle); // if angle is outside [-180°,180°), adds 360°
bool isinsector(int angle,int sectors);

double bintorot(int angle);
double bintogon(int angle);
double bintodeg(int angle);
double bintomin(int angle);
double bintosec(int angle);
double bintorad(int angle);
int rottobin(double angle);
int degtobin(double angle);
int mintobin(double angle);
int sectobin(double angle);
int gontobin(double angle);
int radtobin(double angle);

#define SEC1 1657
#define MIN1 99421
#define DEG1 5965232
#define AT0512 0x80ae90e
// AT0512 is arctangent of 5/12, 22.619865°
#define DEG30 0x0aaaaaab
#define AT34 0x0d1bfae2
// AT34 is arctangent of 3/4, 36.8698976°
#define DEG45 0x10000000
#define DEG60 0x15555555
#define DEG90 0x20000000
#define DEG120 0x2aaaaaab
#define DEG180 0x40000000
#define DEG360 0x80000000
#define PHITURN 0x4f1bbcdd

#endif
