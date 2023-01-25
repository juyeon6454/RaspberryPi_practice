#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmpHeader.h"

typedef unsigned char ubyte;

int main(int argc, char **argv)
{
	FILE *fp;
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	ubyte *inimg, *outimg;
	RGBQUAD *plrgb;

	if((fp = fopen(argv[1], "rb")) == NULL)
	{
		fprintf(stderr, "File not open\n");
		return -1;
	}

	fread(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);
	fread(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, fp);


	int elemsize = bmpInfoHeader.biBitCount/8;
	int size = bmpInfoHeader.biWidth * elemsize;
	int imagesize = bmpInfoHeader.biHeight * size;
	inimg = malloc(sizeof(ubyte)*imagesize);	
	outimg = malloc(sizeof(ubyte)*imagesize);
	plrgb = malloc(sizeof(ubyte)*256);

	fread(inimg, sizeof(ubyte), imagesize, fp);
	fread(outimg, sizeof(ubyte), imagesize, fp);
	fread(plrgb, sizeof(ubyte), 256, fp);

	fclose(fp);


	
	for (int i = 0; i < imagesize; i += elemsize)
	{
			outimg[i+0] = inimg[i+0];
			outimg[i+1] = inimg[i+1];
			outimg[i+2] = inimg[i+2];
	}

	for(int x =0; x <256; x++)
	{
			plrgb[x].rgbBlue = plrgb[x].rgbGreen = plrgb[x].rgbRed = x;
			plrgb[x].rgbReserved = 0;
	}

	if((fp=fopen(argv[2], "wb")) == NULL)
	{
			fprintf(stderr, "File not open\n");
			return -1;
	}

	fwrite(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);
	fwrite(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, fp);

	bmpFileHeader.bfOffBits = sizeof(bmpInfoHeader) + sizeof(bmpFileHeader) + sizeof(plrgb)*256;
	fwrite(outimg, sizeof(ubyte) , imagesize, fp);

	free(inimg);
	free(outimg);
	free(plrgb);

	fclose(fp);
	return 0;
}

