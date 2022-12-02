#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define BYTE unsigned char

#define widthbytes(bits) (((bits)+31)/32*4)
#include "bmpHeader.h"

inline unsigned char clip(int value, int min, int max);
unsigned char clip(int value, int min, int max)
{
    return(value > max? max : value < min? min : value);
}

int main(int argc, char** argv) {
	FILE* fp; 
	RGBQUAD palrgb[256];
	
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;

	/* BMP FILE INFO */
		char input[128], output[128];
	
	int i, j, size; 
	float srcX, srcY;
	int index; 
	float r,g,b,gray;
	int graysize; 
	int index2;
	float rr,gg,bb;	
	unsigned char *grayimg, *inimg, *outimg;
	unsigned imagesize;	
	/* usage a.out in.bmp out.bmp */
	strcpy(input, argv[1]); 
	strcpy(output, argv[2]);
	
	
	if((fp=fopen(input, "rb")) == NULL) { 
		fprintf(stderr, "Error : Failed to open file...₩n"); 
		return -1;
	}
	fread(&bmpFileHeader, sizeof(bmpFileHeader),1,fp);	
	fread(&bmpInfoHeader, sizeof(bmpInfoHeader),1,fp);


	size=widthbytes(bmpInfoHeader.biBitCount * bmpInfoHeader.biWidth); 
	graysize = widthbytes(8 * bmpInfoHeader.biWidth);
	
	if(!imagesize) 
		imagesize=bmpInfoHeader.biHeight*size;
	
	inimg=(BYTE*)malloc(sizeof(BYTE)*imagesize); 
	outimg=(BYTE*)malloc(sizeof(BYTE)*imagesize); 
	fread(inimg, sizeof(BYTE), imagesize, fp); 
	
	fclose(fp);
	
	for(i=0; i<bmpInfoHeader.biHeight*3; i+=3) { 
		for(j=0; j<bmpInfoHeader.biWidth*3; j+=3) {
			int b = inimg[j+(i*bmpInfoHeader.biWidth+0)]; 
			int g = inimg[j+(i*bmpInfoHeader.biWidth+1)]; 
			int r = inimg[j+(i*bmpInfoHeader.biWidth+2)]; 
			
			bb = (r*0.3F)+(g*0.59F)+(b*0.11F);
			gg = (r*0.3F)+(g*0.59F)+(b*0.11F);
			rr = (r*0.3F) + (g*0.59F)+(b*0.11F); 
			
			outimg[j+bmpInfoHeader.biWidth*i+0]= clip(bb, 0, 255);
			outimg[j+bmpInfoHeader.biWidth*i+1]= clip(gg, 0, 255);
			outimg[j+bmpInfoHeader.biWidth*i+2]= clip(rr,0, 255);
		};
	 };	   
	 
	
	size=widthbytes(bmpInfoHeader.biBitCount*bmpInfoHeader.biWidth); 
	imagesize=bmpInfoHeader.biHeight*size; 
	bmpFileHeader.bfOffBits+=256*sizeof(RGBQUAD);
	
	if((fp=fopen(output, "wb"))==NULL) { 
		fprintf(stderr, "Error : Failed to open file...₩n"); 
		return -1;
	}
	fwrite(&bmpFileHeader, sizeof(bmpFileHeader),1,fp);
	fwrite(&bmpInfoHeader, sizeof(bmpInfoHeader),1,fp);
	fwrite(palrgb, sizeof(unsigned int), 256, fp); 
	
	fwrite(outimg, sizeof(unsigned char), imagesize, fp);
	
	free(inimg); 
	free(outimg);
	
	fclose(fp); 
	
	return 0;
}
