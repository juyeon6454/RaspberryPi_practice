#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmpHeader.h"

typedef unsigned char UBYTE;

int main(int argc, char **argv)
{
	FILE *fp;
	UBYTE *inimg, *grayimg, *padimg;
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	RGBQUAD *palrgb;

	if(argc!=3)
	{
		fprintf(stderr, "Usgae : Fail to file open\n");
		return -1;
	}

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
    grayimg = malloc(sizeof(UBYTE)*imagesize);
	palrgb = malloc(sizeof(RGBQUAD)*256);

	fread(inimg, sizeof(UBYTE), imagesize, fp);
	fclose(fp);

	printf("width : %d , height : %d , imagesize : %d ", bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, imagesize);

	for(int x = 0; x < 256 ; x ++){
		
		palrgb[x].rgbBlue = palrgb[x].rgbGreen = palrgb[x].rgbRed = x;	
	}

	for(int i = 0; i < imagesize; i+=elemsize)
	{
			UBYTE b = (float)*(inimg+i+0);
	        UBYTE g = (float)*(inimg+i+1);
	        UBYTE r = (float)*(inimg+i+2);
			
			grayimg[i+0] = grayimg[i+1] = grayimg[i+2] =(r*0.3F)+(g*0.59F)+(b*0.11F);
	}

	int padsize = (bmpInfoHeader.biWidth+2)  * elemsize;
	int addsize = padsize + (bmpInfoHeader.biHeight * elemsize);
	
	padimg = (UBYTE*)malloc(sizeof(UBYTE)*(imagesize + addsize));
	
	memset (padimg, 0 , sizeof(UBYTE)*(imagesize + addsize));
	for(int y = 0; y < bmpInfoHeader.biHeight; y++) {
			for (int x = 0; x < size; x += elemsize)
			{
				padimg[(x+elemsize)+(y+1)*imagesize+0]=grayimg[x+y*imagesize+0];
				padimg[(x+elemsize)+(y+1)*imagesize+1]=grayimg[x+y*imagesize+1];
				padimg[(x+elemsize)+(y+1)*imagesize+2]=grayimg[x+y*imagesize+2];

			}
	}

	//for(y = 0; y < bmpInfoHeader.biHeight; y++) {
	//		for(z=0; z<elemsize; z++)
	//		{
	//			padimg[0+(y+1)*bmpInfoHeader.biHeight*elemsize+z] = grayimg[0+y*bmpInfoHeader.biHeight*elemsize+z];//height*elemsize instead padsize/size?
	//			padimg[(padsize-elemsize)+(y+1)*bmpInfoHeader.biHeight*elemsize+z] = grayimg[(size-elemsize)+y*bmpInfoHeader.biHeight*elemsize];
	//		}
	//}

	//for(x = 0; x < size; x += elemsize){
	//		for(z=0; z<elemsize; z++)
	//{
	//		padimg[x+elemsize+size+z] = grayimg[x+size+z];
	//		padimg[x+elemsize+bmpInfoHeader.biHeightpadsize-
	//}
	//}

	if((fp = fopen(argv[2],"wb"))== NULL)
	{
			fprintf(stderr, "File open fail\n");
			return -1;
	}

	
	fwrite(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);
	fwrite(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, fp);

	
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256;
	//bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256 + sizeof(UBYTE)*imagesize;
	fwrite(padimg, sizeof(UBYTE), imagesize + addsize, fp);
	fwrite(palrgb, sizeof(RGBQUAD)*256, 1, fp);
	free(inimg);
	free(padimg);
	free(palrgb);
	fclose(fp);


	return 0;
}
