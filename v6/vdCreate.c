#include "include/ecdc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv)
{
	if (argc==3) {
		result res = encoder((unsigned char *)argv[2],strlen((const char *)argv[2]));
		if (res.numByte > atoi(argv[2])) {
			printf("Cannot be created\n");
		} else {
			FILE *f = fopen((const char *)argv[1], "wb");
			fwrite(res.output, 1, res.numByte, f);
			char ch = 0;
			for (int i = res.numByte; i < atoi(argv[2]); i++) {
				fseek(f, i * sizeof(char), SEEK_SET);
				fwrite(&ch, 1, 1, f);
			}
			fclose(f);
		}
	}
	else printf("Invalid Number of arguments\n");
	return 0;
}
