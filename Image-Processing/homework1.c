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
		unsigned char *inimg;
		char input[100];
		int imagesize;
	//	int r,g,b;
		strcpy(input, argv[1]);
		if((fp = fopen(input, "rb")) ==NULL){
			fprintf(stderr, "Error : Failed to open file...\n");
			exit(EXIT_FAILURE);
		}

		fread(&bmpFileHeader, sizeof(bmpFileHeader),1,fp);
		fread(&bmpInfoHeader, sizeof(bmpInfoHeader),1,fp);
		printf("width : %d height : %d", bmpInfoHeader.biWidth , bmpInfoHeader.biHeight);	
		//if(!imagesize) imagesize = bmpInfoHeader.biHeight * size;
		int elemsize = bmpInfoHeader.biBitCount/8;
		imagesize = bmpInfoHeader.biHeight * bmpInfoHeader.biWidth * elemsize;
		printf("imagesize : %d " , imagesize);

		inimg =malloc(sizeof(UBYTE)*imagesize);

		fread(inimg, sizeof(UBYTE), imagesize , fp);
		fclose(fp);
	
		for(int i = 0; i < bmpInfoHeader.biHeight; i++) {
				for(int j=0; j<bmpInfoHeader.biWidth * elemsize; j+=elemsize) 
				{

					//printf ("i : %d , j : %d\n", i, j);
					//printf("height : %d , width : %d ", bmpInfoHeader.biHeight, bmpInfoHeader.biWidth);
					int b=inimg[j+i*bmpInfoHeader.biWidth*elemsize+0];
					
					int g=inimg[j+i*bmpInfoHeader.biWidth*elemsize+1];	
							
					int r=inimg[j+i*bmpInfoHeader.biWidth*elemsize+2];
					
					// b = b+ 10;
					// g =g+ 10;
					// r =r+ 10;

				printf ("r : %d / g : %d / b : %d\n", r , g, b);
				}
		}

		free(inimg);
		return 0;
}
