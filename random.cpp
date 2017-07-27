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
