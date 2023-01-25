#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmpHeader.h"

unsigned char UBYTE;

int main(int argc, char **argv)
{
		FILE *fp;
		BITMAPFILEHEADER bmpFileHeader;
		BITMAPINFOHEADER bmpInfoHeader;
		char input[100];
		unsigned char *inimg;
		int elemsize = bmpInfoHeader.biBitCount/8;
		int imagesize = bmpInfoHeader.biHeight * bmpInfoHeader.biWidth * elemsize;
 		strcpy(input, argv[1]);
		if((fp = fopen(input, "rb")) == NULL)		{
			fprintf(stderr,"File open to fail\n");
			return -1; // MEMORY FREE FIRST
		}

		fread(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);
		fread(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, fp);

		inimg = malloc(sizeof(UBYTE)*imagesize);

		fread(inimg, sizeof(UBYTE), imagesize, fp);
		fclose(fp);
		for(int i = 0; i < bmpInfoHeader.biHeight; i++) {
				for(int j = 0; j < bmpInfoHeader.biWidth * elemsize; j+=elemsize){
						int b = inimg[j + i * bmpInfoHeader.biWidth * elemsize + 0];
						int g = inimg[j + i * bmpInfoHeader.biWidth * elemsize + 1];
						int r = inimg[j + i * bmpInfoHeader.biWidth * elemsize + 2];

						printf (" r : %d , g : %d, b : %d " ,r, g, b );
						}
		}

		free(inimg);


		return 0;
}
