#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmpHeader.h"

typedef unsigned char UBYTE;

int main(int argc, char **argv)

{
	FILE *fp;
	UBYTE *inimg, *outimg;
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	RGBQUAD *palrgb;
	int r,g,b;

	if((fp = fopen(argv[1],"rb"))==NULL)
	{
			fprintf(stderr, "Usage : Fail to file open\n");
			return -1;
	}

	fread(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);
	fread(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, fp);
	int elemsize = bmpInfoHeader.biBitCount/8;
	int imagesize = bmpInfoHeader.biWidth * bmpInfoHeader.biHeight * elemsize;	
	printf("width : %d , height : %d , elemsize : %d ", bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, elemsize);
	int size = bmpInfoHeader.biWidth * elemsize;
	inimg = malloc(sizeof(UBYTE)*imagesize);
    outimg = malloc(sizeof(UBYTE)*imagesize);
	palrgb = malloc(sizeof(RGBQUAD)*256);

	fread(inimg, sizeof(UBYTE), imagesize, fp);
	fread(outimg, sizeof(UBYTE), imagesize, fp);
	fread(palrgb, sizeof(RGBQUAD)*256, 1, fp);
	fclose(fp);


	printf("width : %d , height : %d , imagesize : %d ", bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, imagesize);

	for(int i = 0; i < bmpInfoHeader.biHeight; i++)
	{
			for(int j=0; j < size; j +=elemsize)
			{
					//int b = inimg[i + j * size + 0];
					//int g = inimg[i + j * size + 1];
					//int r = inimg[i + j * size + 2];

					//printf ("r : %d, g : %d, b : %d" , r, g, b);
					outimg[j+i*size+0] = inimg [j+i*size+0];
					outimg[j+i*size+1] = inimg [j+i*size+1];
					outimg[j+i*size+2] = inimg [j+i*size+2];
					//printf ("r : %d, g : %d, b : %d\n" , r, g, b);
			}
	}
	if((fp = fopen(argv[2],"wb"))== NULL)
	{
			fprintf(stderr, "File open fail\n");
			return -1;
	}


	for(int x = 0; x < 256 ; x ++){
			
		 palrgb[x].rgbBlue= palrgb[x].rgbGreen = palrgb[x].rgbRed = x;
		 palrgb[x].rgbReserved = 0;
	}

	
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256;
	bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256 + sizeof(UBYTE)*imagesize;
	fwrite(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);
	fwrite(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, fp);
	fwrite(outimg, sizeof(UBYTE), imagesize, fp);
	fwrite(palrgb, sizeof(RGBQUAD)*256, 1, fp);
	free(inimg);
	free(outimg);
	//free(palrgb);
	fclose(fp);

	return 0;
}
