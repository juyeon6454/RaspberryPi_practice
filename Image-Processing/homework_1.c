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
		unsigned char *inimg, *outimg;
		char input[100], output[100];
		int imagesize;
		strcpy(input, argv[1]);
		strcpy(output, argv[2]);

		if(argc !=3) {
			fprintf(stderr, "%s usage : input.bmp output.bmp\n", argv[0]);
			return -1;
		}

		if((fp = fopen(argv[1],"rb")) ==NULL){
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
		outimg =malloc(sizeof(UBYTE)*imagesize);

		fread(inimg, sizeof(UBYTE)*imagesize, 1, fp);
		fread(outimg, sizeof(UBYTE)*imagesize, 1, fp);
		fclose(fp);	
		for(int i = 0; i < bmpInfoHeader.biHeight; i++) {
				for(int j=0; j<bmpInfoHeader.biWidth * elemsize; j+=elemsize) 
				{
							outimg[j+(i*bmpInfoHeader.biWidth*elemsize+0)]=inimg[j+(i*bmpInfoHeader.biWidth * elemsize + 0)];
					
							outimg[j+(i*bmpInfoHeader.biWidth*elemsize+1)]=inimg[j+(i*bmpInfoHeader.biWidth * elemsize + 1)];	
							
							outimg[j+(i*bmpInfoHeader.biWidth*elemsize+2)]=inimg[j+(i*bmpInfoHeader.biWidth * elemsize + 2)];
				}
		}
		if((fp = fopen(argv[2], "wb")) == NULL){
				fprintf(stderr, "Error : Failed to open file...\n");
				exit(EXIT_FAILURE);
		}
		fwrite(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);
		fwrite(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, fp);

		fwrite(outimg, sizeof(UBYTE)*imagesize, 1, fp);
		free(inimg);
		free(outimg);
	    fclose(fp);
		return 0;
}
