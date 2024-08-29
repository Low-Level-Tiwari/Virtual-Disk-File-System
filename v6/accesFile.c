#include "include/ecdc.h"
#include <stdio.h>
void acces(unsigned char *out,int numbt) {
  // int reqbits = (8 * (strlen(out) + 1));
  int reqbits = numbt * 8;
  printf("access : %d\n", reqbits);
  int i = 0;
  int bitsDone = 0;
  printf("\n");
  while (i < reqbits) {
    if ((*(out + (i / 8)) & (mask(i % 8))) != 0)
      printf("1");
    else
      printf("0");
    i += 1;
    (i % 8 == 0) ? printf("  ") : printf("");
  }
  printf("\n");
}
int main(int argc, char **argv) {
  FILE *f = fopen((const char*)argv[1], "rb");
  fseek(f,0,SEEK_END);
  int numbytes = ftell(f);
  fseek(f,0,SEEK_SET);
  unsigned char buffer[numbytes];

  fread(buffer, 1,numbytes,f);
  acces(buffer,numbytes);
}
