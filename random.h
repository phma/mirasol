#include "config.h"

class randm
{
public:
  randm();
  unsigned int uirandom();
  unsigned short usrandom();
  unsigned char ucrandom();
  ~randm();
private:
#ifdef HAVE_WINDOWS_H
  unsigned int usbuf,ucbuf,usnum,ucnum;
#else
  FILE *randfil;
#endif
};

extern randm rng;
