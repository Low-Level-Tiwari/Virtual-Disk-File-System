#include <math.h>
#include <stdlib.h>

#define clm(x) (memset(x, 0, sizeof(x)))

#define mask(a) 1 << (a)

typedef struct {
  unsigned char *output;
  int numByte;
} result;
result encoder(unsigned char *, int);

result decoder(unsigned char *out);

