#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <unistd.h>
#include "bmpHeader.h"

#define LIMIT_UBYTE(n) ((n)>UCHAR_MAX)?UCHAR_MAX:((n)<0)?0:(n)

typedef unsigned char ubyte;
 
inline unsigned char clip(int value, int min, int max);

unsigned char clip(int value, int min, int max)
{
	return(value > max ? max : value < min ? min : value);
}
int main(int argc, char** argv)
{
	FILE* fp;
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	//RGBQUAD* palrgb;
	ubyte* inimg, * outimg, * grayimg;
	int arr[9] = { 0, };
	int x, y, z;

	if (argc != 3) {
		fprintf(stderr, "usage : %s input.bmp output.bmp\n", argv[0]);
		return -1;
	}

	if ((fp = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "Error : Failed to open file...\n");
		return -1;
	}

	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

	if (bmpInfoHeader.biBitCount != 24) {
		perror("This image file doesn't supports 24bit color\n");
		fclose(fp);
		return -1;
	}

	int elemSize = bmpInfoHeader.biBitCount / 8;
	int size = bmpInfoHeader.biWidth * elemSize;
	int imageSize = size * bmpInfoHeader.biHeight;

	printf("Resolution : %d x %d\n", bmpInfoHeader.biWidth, bmpInfoHeader.biHeight);
	printf("Bit Count : %d\n", bmpInfoHeader.biBitCount);  
	printf("Image Size : %d\n", imageSize);

	inimg = (ubyte*)malloc(sizeof(ubyte) * imageSize);
	outimg = (ubyte*)malloc(sizeof(ubyte) * imageSize);
	
	fread(inimg, sizeof(ubyte), imageSize, fp);

	//grayimg = (ubyte*)malloc(sizeof(ubyte) * imageSize);
	
	fclose(fp);

	for (int i = 0; i < imageSize; i += elemSize) {
		ubyte r = (float)inimg[i + 0];
		ubyte g = (float)inimg[i + 1];
		ubyte b = (float)inimg[i + 2];

		//grayimg[i + 0] = grayimg[i + 1] = grayimg[i + 2] = (r * 0.3F) + (g * 0.59F) + (b * 0.11F);
		outimg[i + 0] = outimg[i + 1] = outimg[i + 2] = (r * 0.3F) + (g * 0.59F) + (b * 0.11F);
	};
	
	float x_kernel[3][3] = { {-1, 0, 1},
						   {-2,  0, 2},
						   {-1, 0, 1}};

	float y_kernel[3][3] = { {1, 2, 1},
						{0, 0, 0},
						{-1, -2, -1} };

	memset(outimg, 0, sizeof(ubyte) * imageSize);

	for (y = 0; y < bmpInfoHeader.biHeight; y++) {
		for (x = 0; x < bmpInfoHeader.biWidth * elemSize; x += elemSize) {
			for (z = 0; z < elemSize; z++) {
				outimg[(x+elemSize)+(y+1)*size+z]=inimg[(x + elemSize) + (y + 1) * size + z];
				//padimg[(x + elemSize) + (y + 1) * padSize + z] = grayimg[x + y * size + z];
			}
		}
	}
	
	int cnt = 0;

	for (y = 0; y < bmpInfoHeader.biHeight; y++) {
		for (x = 0; x < (bmpInfoHeader.biWidth) * elemSize; x += elemSize) {
			for (z = 0; z < elemSize; z++) {
				if (x == 0) {
					//LeftUpVertex
					if (y == 0) {
						arr[0] = arr[1] = arr[3] = arr[4] = inimg[x + (y * size) + z];
						arr[2] = arr[5] = inimg[x + elemSize + (y * size) + z];
						arr[6] = arr[7] = inimg[x + ((y + 1) * size) + z];
						arr[8] = inimg[x + elemSize + ((y + 1) * size) + z];
					}
					//LeftDownVertex
					else if (y == bmpInfoHeader.biHeight - 1) {
						arr[0] = arr[1] = inimg[x + ((y - 1) * size) + z];
						arr[2] = inimg[x + elemSize + ((y - 1) * size) + z];
						arr[3] = arr[6] = arr[7] = arr[4] = inimg[x + (y * size) + z];
						arr[8] = arr[5] = inimg[x + elemSize + (y * size) + z];
					}
					else {
						arr[0] = arr[1] = inimg[x + ((y - 1) * size) + z];
						arr[2] = inimg[x + elemSize + ((y - 1) * size) + z];
						arr[3] = arr[4] = inimg[x + (y * size) + z];
						arr[5] = inimg[x + elemSize + (y * size) + z];
						arr[6] = arr[7] = inimg[x + ((y + 1) * size) + z];
						arr[8] = inimg[x + elemSize + ((y + 1) * size) + z];
					}

					cnt = 0;
					float sum = 0;
					float xk = 0.0;
					float yk = 0.0;

					for (int i = -1; i < 2; i++) {
						for (int j = -1; j < 2; j++) {
							xk += x_kernel[i + 1][j + 1] * arr[cnt++];
							yk += y_kernel[i + 1][j + 1] * arr[cnt++];
						}
					}
					sum = sqrt(xk * xk + yk * yk);
					outimg[(x + y * size) + z] = clip(sum, 0, 255);
				}

				else if (x == (bmpInfoHeader.biWidth * elemSize - elemSize)) {
					//RightUpVertex
					if (y == 0) {
						arr[0] = arr[3] = inimg[x - elemSize + (y * size) + z];
						arr[1] = arr[2] = arr[5] = arr[4] = inimg[x + (y * size) + z];
						arr[6] = inimg[x - elemSize + ((y - 1) * size) + z];
						arr[7] = arr[8] = inimg[x + ((y + 1) * size) + z];
					}
					//RightDownVertex
					else if (y == bmpInfoHeader.biHeight - 1) {
						arr[0] = inimg[x - elemSize + ((y - 1) * size) + z];
						arr[1] = arr[2] = inimg[x - elemSize + ((y - 1) * size) + z];
						arr[3] = arr[6] = inimg[x - elemSize + (y * size) + z];
						arr[4] = arr[5] = arr[7] = arr[8] = inimg[x + (y * size) + z];
					}
					else {
						arr[0] = inimg[x - elemSize + ((y - 1) * size) + z];
						arr[2] = arr[1] = inimg[x + ((y - 1) * size) + z];
						arr[3] = inimg[x - elemSize + (y * size) + z];
						arr[5] = arr[4] = inimg[x + (y * size) + z];
						arr[6] = inimg[x - elemSize + ((y + 1) * size) + z];
						arr[8] = arr[7] = inimg[x + ((y + 1) * size) + z];
					}
					cnt = 0;
					float sum = 0.0;
					float xk = 0.0;
					float yk = 0.0;

					for (int i = -1; i < 2; i++) {
						for (int j = -1; j < 2; j++) {
							xk += x_kernel[i + 1][j + 1] * arr[cnt++];
							yk += y_kernel[i + 1][j + 1] * arr[cnt++];
						}
					}
					sum = sqrt(xk * xk + yk * yk);
					outimg[(x + y * size) + z] = clip(sum, 0, 255);
				}
				else if (y == 0) {
					if (x != 1 && x != size - elemSize) {
						arr[0] = arr[3] = inimg[x - elemSize + (y * size) + z];
						arr[1] = arr[4] = inimg[x + (y * size) + z];
						arr[2] = arr[5] = inimg[x + elemSize + (y * size) + z];
						arr[6] = inimg[x - elemSize + ((y + 1) * size) + z];
						arr[7] = inimg[x + ((y + 1) * size) + z];
						arr[8] = inimg[x + elemSize + ((y + 1) * size) + z];

						cnt = 0;
						float sum = 0.0;
						float xk = 0.0;
						float yk = 0.0;
						for (int i = -1; i < 2; i++) {
							for (int j = -1; j < 2; j++) {
								xk += x_kernel[i + 1][j + 1] * arr[cnt++];
								yk += y_kernel[i + 1][j + 1] * arr[cnt++];
							}
						}
						sum = sqrt(xk * xk + yk * yk);
						outimg[(x + y * size) + z] = clip(sum, 0, 255);
					}
				}
				else if (y == (bmpInfoHeader.biHeight - 1)) {
					if (x != 1 && x != size - elemSize) {
						arr[0] = inimg[x - elemSize + ((y - 1) * size) + z];
						arr[1] = inimg[x + ((y - 1) * size) + z];
						arr[2] = inimg[x + elemSize + ((y - 1) * size) + z];
						arr[3] = arr[6] = inimg[x - elemSize + (y * size) + z];
						arr[4] = arr[7] = inimg[x + (y * size) + z];
						arr[5] = arr[8] = inimg[x + elemSize + (y * size) + z];
						cnt = 0;
						float sum = 0.0;
						float xk = 0.0;
						float yk = 0.0;
						for (int i = -1; i < 2; i++) {
							for (int j = -1; j < 2; j++) {
								xk += x_kernel[i + 1][j + 1] * arr[cnt++];
								yk += y_kernel[i + 1][j + 1] * arr[cnt++];
							}
						}
						sum = sqrt(xk * xk + yk * yk);
						outimg[(x + y * size) + z] = clip(sum, 0, 255);
					}
				}

				else {
					float sum = 0.0;
					float xk = 0.0;
					float yk = 0.0;
					for (int i = -1; i < 2; i++) {
						for (int j = -1; j < 2; j++) {
							xk += x_kernel[i + 1][j + 1] * arr[cnt++];
							yk += y_kernel[i + 1][j + 1] * arr[cnt++];
						}
					}
					sum = sqrt(xk * xk + yk * yk);
					outimg[(x + y * size) + z] = clip(sum, 0, 255);
					//outimg[(x - elemSize) + (y - 1) * size + z] = LIMIT_UBYTE(sum);
				}

			}
		}


		//memset(outimg, 0, sizeof(ubyte) * imageSize);


		if ((fp = fopen(argv[2], "wb")) == NULL) {
			fprintf(stderr, "Error : Failed to open file... \n");
			return -1;
		}

		fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
		fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
		fwrite(outimg, sizeof(ubyte), imageSize, fp);

		fclose(fp);

		free(inimg);
		free(outimg);

		return 0;
	}
}
