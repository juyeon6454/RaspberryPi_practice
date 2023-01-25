#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <limits.h>                     /* USHRT_MAX  곸닔瑜   꾪빐    ъ슜 쒕떎. */
#include <unistd.h>
#include <math.h>
#include "bmpHeader.h"

/*  대 吏   곗씠 곗쓽 寃쎄퀎 寃  щ   꾪븳 留ㅽ겕濡  */
#define LIMIT_UBYTE(n) ((n)>UCHAR_MAX)?UCHAR_MAX:((n)<0)?0:(n)

typedef unsigned char ubyte;

int main(int argc, char** argv) 
{
    FILE* fp; 
    BITMAPFILEHEADER bmpHeader;             /* BMP FILE INFO */
    BITMAPINFOHEADER bmpInfoHeader;     /* BMP IMAGE INFO */
    RGBQUAD *palrgb;
    ubyte *inimg, *padimg, *outimg, *grayimg;

    int x, y, z, imageSize;

    if(argc != 3) {
        fprintf(stderr, "usage : %s input.bmp output.bmp\n", argv[0]);
        return -1;
    }
    
    /***** read bmp *****/ 
    if((fp=fopen(argv[1], "rb")) == NULL) { 
        fprintf(stderr, "Error : Failed to open file... 쯰"); 
        return -1;
    }

    /* BITMAPFILEHEADER 援ъ“泥댁쓽  곗씠   */
    fread(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);

    /* BITMAPINFOHEADER 援ъ“泥댁쓽  곗씠   */
    fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    /*  몃（ 而щ윭瑜  吏  먰븯硫  蹂  섑븷     녿떎. */
    if(bmpInfoHeader.biBitCount != 24) {
        perror("This image file doesn't supports 24bit color\n");
        fclose(fp);
        return -1;
    }
    
    int elemSize = bmpInfoHeader.biBitCount/8;
    int size = bmpInfoHeader.biWidth*elemSize;
    imageSize = size * bmpInfoHeader.biHeight; 

    /*  대 吏     댁긽  ( 볦씠 횞 源딆씠) */
    printf("Resolution : %d x %d\n", bmpInfoHeader.biWidth, bmpInfoHeader.biHeight);
    printf("Bit Count : %d\n", bmpInfoHeader.biBitCount);     /*  쎌    鍮꾪듃   ( 됱긽) */
    printf("Image Size : %d\n", imageSize);

    inimg = (ubyte*)malloc(sizeof(ubyte)*imageSize); 
    outimg = (ubyte*)malloc(sizeof(ubyte)*imageSize);
    fread(inimg, sizeof(ubyte), imageSize, fp); 
	grayimg = (ubyte*)malloc(sizeof(ubyte)*imageSize);
    fclose(fp);
	printf("62 : imageSize : %d\n",imageSize);

	   	for(int i = 0; i < imageSize; i+=elemSize) {
		 ubyte r = (float)inimg[i+0];
         ubyte g = (float)inimg[i+1];
         ubyte b = (float)inimg[i+2];


         grayimg[i+0] = grayimg[i+1] = grayimg[i+2] =(r*0.3F)+(g*0.59F)+(b*0.11F);
	};

    int padSize = (bmpInfoHeader.biWidth + 2) * elemSize;
    int addSize = (padSize + bmpInfoHeader.biHeight)*2;
    padimg = (ubyte*)malloc(sizeof(ubyte)*(imageSize + addSize));
	printf("76 : imageSize : %d\n",imageSize);

    /* make padding image */
    memset(padimg, 0, (sizeof(ubyte)*imageSize + addSize));
    //memset(outimg, 0, sizeof(ubyte)*imageSize);
    for(y = 0; y < bmpInfoHeader.biHeight; y++) {
        for(x = 0; x < bmpInfoHeader.biWidth * elemSize; x+=elemSize) {
            for(z = 0; z < elemSize; z++) {
                //outimg[(x+elemSize)+(y+1)*size+z]=inimg[x+y*size+z];
                padimg[(x+elemSize)+(y+1)*padSize+z]=grayimg[x+y*size+z];
            }
        }
    }
	printf("89 : imageSize : %d\n",imageSize);

    for(y = 0; y < bmpInfoHeader.biHeight; y++) { 
        for(z = 0; z < elemSize; z++) {
            padimg[0+(y+1)*padSize+z]=grayimg[0+y*size+z];
            padimg[padSize-elemSize+(y+1)*padSize+z]=grayimg[size-elemSize+y*size+z];
        }
    }
	printf("97 : imageSize : %d\n",imageSize);

    for(x = 0; x < bmpInfoHeader.biWidth*elemSize; x++) { 
        padimg[elemSize+x]=grayimg[x];
        padimg[elemSize+x+(bmpInfoHeader.biHeight+1)*padSize]=grayimg[x+(bmpInfoHeader.biHeight-1)*size];
    }
	printf("103 : imageSize : %d\n",imageSize);

    for(z = 0; z < elemSize; z++) {
       padimg[z]=grayimg[z];
       padimg[padSize-elemSize+z]=grayimg[size-elemSize+z];
       padimg[(bmpInfoHeader.biHeight+2)*padSize+z]=grayimg[(bmpInfoHeader.biHeight-1)*size+z];
       padimg[(bmpInfoHeader.biHeight+2)*padSize+padSize-elemSize+z]=grayimg[(bmpInfoHeader.biHeight-1)*size+size-elemSize+z];
	printf("110 : imageSize : %d\n",imageSize);
    }

    // define the kernel
	printf("109 : imageSize : %d\n",imageSize);
    float x_kernel[3][3] = { {-1, 0,0} ,
                           {0,  1,0 },
                           {0, 0, 0} };

	float y_kernel[3][3] = {{0, 0, -1},
							{0, 1,0 },
							{0, 0, 0}};

    memset(outimg, 0, sizeof(ubyte)*imageSize);
    for(y = 1; y < bmpInfoHeader.biHeight + 1; y++) { 
        for(x = elemSize; x < padSize; x+=elemSize) {
            for(z = 0; z < elemSize; z++) {
                float sum = 0.0;
				float hedge = 0.0;
				float vedge = 0.0;
                for(int i = -1; i < 2; i++) {
                    for(int j = -1; j < 2; j++) {
                        hedge +=x_kernel[i+1][j+1]*padimg[(x+i*elemSize)+(y+j)*padSize+z];
						vedge +=y_kernel[i+1][j+1]*padimg[(x+i*elemSize)+(y+j)*padSize+z];
                    }
                }
				sum = sqrt(hedge*hedge+vedge*vedge);
                outimg[(x-elemSize)+(y-1)*size+z] = LIMIT_UBYTE(sum);
            }
        }                                 
    }         
	printf("gray : %d, out : %d\n",grayimg,outimg);
    
    /***** write bmp *****/ 
    if((fp=fopen(argv[2], "wb"))==NULL) { 
        fprintf(stderr, "Error : Failed to open file... 쯰"); 
        return -1;
    }

    /* BITMAPFILEHEADER 援ъ“泥댁쓽  곗씠   */
    fwrite(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);

    /* BITMAPINFOHEADER 援ъ“泥댁쓽  곗씠   */
    fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    //fwrite(inimg, sizeof(ubyte), imageSize, fp); 
    //fwrite(padimg, sizeof(ubyte), imageSize, fp);
    fwrite(outimg, sizeof(ubyte), imageSize, fp);

    fclose(fp); 

    free(inimg); 
    free(outimg);
    free(padimg);
    
    return 0;
}
