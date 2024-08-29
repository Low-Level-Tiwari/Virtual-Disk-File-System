#include "include/ecdc.h"
#include <stdio.h>
#include <string.h>
int cmp(char *s, char *d)
{
	while (*s && *d)
		if (*s++ != *d++)
			return 1;
	if (*s || *d)
		return 1;
	return 0;
}
int main(int argc, char **argv)
{
	if (2 == argc) {
		unsigned char buffer[100];
		result res,res1;
		char ch;
		int bytesRead=0;
		char status = 0;
		FILE *f = fopen((const char *)argv[1], "rb");
		fseek(f, 0, SEEK_SET);
		fread(buffer, sizeof(unsigned char), sizeof(buffer), f);
		res = decoder(buffer);
		int prev = atoi((const char *)res.output);
		clm(buffer);
		bytesRead += res.numByte;
		while (status == 0) {
			fseek(f, bytesRead, SEEK_SET);
			fread(buffer, sizeof(unsigned char), sizeof(buffer), f);
			res = decoder(buffer);
			if (*res.output == '\0') {
				status = 1;
			} else {

				if (prev == bytesRead + 1)status = 2;
				else{
				bytesRead += res.numByte;
				fseek(f, bytesRead, SEEK_SET);
				clm(buffer);
				fread(buffer, sizeof(unsigned char),sizeof(buffer), f);
				res1 = decoder(buffer);
				if(*res1.output == '\0'){
					bytesRead+=res1.numByte;
					fseek(f, bytesRead, SEEK_SET);
					while(fgetc(f)==0){
						bytesRead +=1; 
					}
					fseek(f,-1,SEEK_CUR);
					clm(buffer);
					fread(buffer, sizeof(unsigned char),sizeof(buffer), f);
					res1 = decoder(buffer);
				}else{	
				printf("    %s\t", res.output);
				printf("%s\n", res1.output);
				bytesRead += res1.numByte;
				fseek(f, bytesRead, SEEK_SET);
				clm(buffer);
				fread(buffer, sizeof(unsigned char),sizeof(buffer), f);
				res1 = decoder(buffer);
				}
				bytesRead += res1.numByte;
				prev = *((int *)res1.output);
				clm(buffer);
				}
			}
		}
		fclose(f);
	} else {
		printf("Too few arguments\n");
	}
	return 0;
}
