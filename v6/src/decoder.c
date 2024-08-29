#include"../include/ecdc.h"
#include<stdlib.h>
#include<math.h>


#define mask(a) 1 << (a)
result decoder(unsigned char *out)
{

	result res;
	res.numByte=0;
	res.output=(unsigned char*)calloc(1,sizeof(unsigned char));
	int i = 0, bitsDone = 8;
	unsigned char flg = 1, buf = 0;
	int byte=-1;
	while (flg == 1) {
		buf = 0;
		// Check 01 pattern
		if (bitsDone == 8) {
			buf |= (((*(out + (i/8)) & mask((i%8))) != 0) ? 1 : 0);
			buf = buf << 1;
			i += 1;
			buf |=(((*(out + (i/8)) & mask((i%8))) != 0) ? 1 : 0);

			// 01 means one more byte
			if (buf == 1) {
				bitsDone = 0;
				byte++;
				//res.numByte++;
				res.output=(unsigned char*)realloc(res.output,byte+1);
			} 
			// Any other pattern means End of Sequence
			else { 
				flg = 0;
			}
		}
	       // Byte data reading	
		else {
			res.output[byte] = res.output[byte] << 1;
			res.output[byte] |= (((*(out + (i/8)) & mask((i%8))) != 0) ? 1 : 0);
			bitsDone += 1;
		}
		i += 1;
	}
	res.numByte = (int)ceil(i/8.0);
	return res;
}


