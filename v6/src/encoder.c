#include"../include/ecdc.h"
#include<stdlib.h>
#define mask(a) 1 << (a)

result encoder(unsigned char *num,int numc)
{
	int reqbits = ceil((numc * 2.0 + 2 + numc * 8) / 8);
	result out;
	out.output = (unsigned char *)calloc(reqbits,sizeof(unsigned char));
	int bitsDone = 0;
	int i = (numc*2 + 2 + numc*8)-3;
	unsigned char k;
	numc--;
	bitsDone = 0;
	k=num[numc];
	out.numByte = reqbits;
	while (i >= 0&&numc>=0) {
	
		// Insert 01 pattern
		if (bitsDone == 8) {
			*(out.output + (i / 8)) |= mask(i % 8);
			i -= 1;
			bitsDone = 0;
			numc--;
			if(numc>=0)k=num[numc];
		}

	       // Byte data reading	
		else 
		{
			if (k & 1) {
				*(out.output + (i / 8)) |= mask((i % 8));
			}
			k = (k>>1);
			bitsDone += 1;
		}
		i -= 1;
	}
	return out;
}

