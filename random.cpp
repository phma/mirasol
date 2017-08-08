/******************************************************/
/*                                                    */
/* random.cpp - random numbers                        */
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
#define _CRT_RAND_S
#include <cstdlib>
#include <cstdio>
#include "random.h"

#ifdef HAVE_WINDOWS_H
randm::randm()
{
  ucnum=usnum=0;
}

randm::~randm()
{
  ucnum=usnum=-1;
}

unsigned int randm::uirandom()
{
  unsigned int n;
  rand_s(&n);
  return n;
}

unsigned short randm::usrandom()
{
  unsigned short n;
  if (!usnum)
    rand_s(&usbuf);
  n=(usbuf>>usnum)&0xffff;
  usnum=(usnum+16)&31;
  return n;
}

unsigned char randm::ucrandom()
{
  unsigned char n;
  if (!ucnum)
    rand_s(&ucbuf);
  n=(ucbuf>>ucnum)&0xff;
  ucnum=(ucnum+8)&31;
  return n;
}
#else
randm::randm()
{
  randfil=fopen("/dev/urandom","rb");
}

randm::~randm()
{
  fclose(randfil);
}

unsigned int randm::uirandom()
{
  unsigned int n;
  fread(&n,1,4,randfil);
  return n;
}

unsigned short randm::usrandom()
{
  unsigned short n;
  fread(&n,1,2,randfil);
  return n;
}

unsigned char randm::ucrandom()
{
  unsigned char n;
  fread(&n,1,1,randfil);
  return n;
}
#endif

randm rng;
