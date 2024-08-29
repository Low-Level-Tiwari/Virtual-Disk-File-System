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
	if (3 == argc) {
		unsigned char buffer[100],flg;
		result res;
		int size = 0, count = 0, bytesRead = 0, prev = 0;
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
					printf("%s:%s|\n",res.output,argv[2]);
					flg = cmp(res.output,argv[2]);
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
					if(!flg)
					{
						clm(buffer);
						//unsigned char c=0;
						fseek(f, bytesRead, SEEK_SET);
						fwrite(buffer,1,res.numByte,f);		
						status=3;
					}
					bytesRead += res.numByte;
					fseek(f, bytesRead, SEEK_SET);
					clm(buffer);
					fread(buffer, sizeof(unsigned char),sizeof(buffer), f);
					res = decoder(buffer);
				}
					bytesRead += res.numByte;
					prev = *((int *)res.output);
					clm(buffer);
				}
			}
		}
		printf("STATUS :: %d\n",status);
		if (status == 3) {
			printf("File deleted\n");
		} 
		else {
			printf("File Not found\n");
		}
		fclose(f);
	} else {
		printf("Too few arguments\n");
	}
	return 0;
}
