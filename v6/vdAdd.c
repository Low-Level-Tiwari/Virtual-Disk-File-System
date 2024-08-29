#include "include/ecdc.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
	if (4 == argc) {
		unsigned char buffer[100];
		result res, res2, res3;
		int size = 0, count = 0, bytesRead = 0, totalFileSizes=0, prev = 0;
		char status = 0, c;
		FILE *f = fopen((const char *)argv[1], "rb+");
		fseek(f, 0, SEEK_SET);
		fread(buffer, sizeof(unsigned char), sizeof(buffer), f);
		res = decoder(buffer);
		clm(buffer);
		size = atoi((const char *)res.output);
		prev = size;
		bytesRead += res.numByte;
		while (status == 0) {
			fseek(f, bytesRead, SEEK_SET);
			fread(buffer, sizeof(unsigned char), sizeof(buffer), f);
			res = decoder(buffer);
			if (*res.output == '\0') {
				status = 1;
			} else {
				if (prev == bytesRead + 1) {
					status = 2;
				} else {
					bytesRead += res.numByte;
					fseek(f, bytesRead, SEEK_SET);
					clm(buffer);
					fread(buffer, sizeof(unsigned char),sizeof(buffer), f);
					res = decoder(buffer);
					if(*res.output == '\0'){
						bytesRead+=res.numByte;
						fseek(f, bytesRead, SEEK_SET);
						while(fgetc(f)==0){
							bytesRead +=1; 
						}
						fseek(f,-1,SEEK_CUR);
						clm(buffer);
						fread(buffer, sizeof(unsigned char),sizeof(buffer), f);
						res = decoder(buffer);
				}else{	
					bytesRead += res.numByte;
					fseek(f, bytesRead, SEEK_SET);
					clm(buffer);
					fread(buffer, sizeof(unsigned char),sizeof(buffer), f);
					res = decoder(buffer);
					totalFileSizes +=(prev - *((int *)res.output));
				}
					bytesRead += res.numByte;
					prev = *((int *)res.output);
					clm(buffer);
				}
			}
		}
		if (status == 1) {
			int start = prev - atoi((const char *)argv[3]);	
			res = encoder((unsigned char *)&start, sizeof(int));
			res2 = encoder((unsigned char *)argv[2], strlen(argv[2]));
			res3 = encoder((unsigned char *)argv[3], strlen(argv[3]));
			if ((res.numByte + atoi((const char *)argv[3])+res2.numByte + res3.numByte) <= 
				(size - (bytesRead + totalFileSizes))) {
				fseek(f, bytesRead, SEEK_SET);
				fwrite(res2.output, 1, res2.numByte, f);
				fwrite(res3.output, 1, res3.numByte, f);
				fwrite(res.output, 1, res.numByte, f);
				fseek(f, start, SEEK_SET);
				// copy the file accordingly
				FILE *uf = fopen(argv[2], "rb");
				while ((c = fgetc(uf)) != EOF)
					fwrite(&c, 1, 1, f);
				fclose(uf);
			} else {
				printf("Not enough space\n");
			}
		} else {
			printf("No space left\n");
		}
		fclose(f);
	} else {
		printf("Too few arguments\n");
	}
	return 0;
}
