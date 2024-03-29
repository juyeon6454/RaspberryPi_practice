#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmpHeader.h"

typedef unsigned char UBYTE;

int main(int argc, char *argv[])
{
	FILE *fp;
	UBYTE *inimg, *outimg;
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	RGBQUAD *palrgb;
//	if(argc!=3)
//	{
//		fprintf(stderr, "Usgae : Fail to file open\n");
//		return -1;
//	}

//	if((fp = fopen(argv[1],"rb"))==NULL)
//	{
//			fprintf(stderr, "Usage : Fail to file open\n");
//			return -1;
//	}

	if((fp = fopen(*(argv+1),"rb"))==NULL)
			
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


	for(int i = 0; i < imagesize; i+=elemsize)
	{
			//outimg[i+0] = inimg[i+0];
			//outimg[i+1] = inimg[i+1];
			//outimg[i+2] = inimg[i+2];
			*(outimg+i+0) =*(inimg+i+0);
		    *(outimg+i+1) =*(inimg+i+1);
			*(outimg+i+2) =*(inimg+i+2);
			
	}
	

	if((fp = fopen(*(argv+2),"wb"))== NULL)
	{
			fprintf(stderr, "File open fail\n");
			return -1;
	}


	for(int x = 0; x < 256 ; x ++){
			
		 palrgb[x].rgbBlue= palrgb[x].rgbGreen = palrgb[x].rgbRed = x;
		 palrgb[x].rgbReserved = 0;
	}
	fwrite(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);
	fwrite(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, fp);

	
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256;
	//bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256 + sizeof(UBYTE)*imagesize;
	fwrite(outimg, sizeof(UBYTE), imagesize, fp);
	fwrite(palrgb, sizeof(RGBQUAD)*256, 1, fp);
	free(inimg);
	free(outimg);
	free(palrgb);
	fclose(fp);


	return 0;
}
