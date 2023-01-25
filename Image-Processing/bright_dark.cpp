#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
		Mat image = imread("./lena.bmp", IMREAD_GRAYSCALE);
		CV_Assert(!image.empty());

		Mat dst1 = image + 100;
		Mat dst2 = image - 100;
		Mat dst3 = 255 - image;

		Mat dst4(image.size(), image.type());
		Mat dst5(image.size(), image.type());
		for(int i = 0; i < image.rows; i++) {
				for (int j = 0; j < image.cols; j++)
				{
						dst4.at<uchar>(i, j) = image.at<uchar>(i,j)+  100;
						//dst4.at<uchar>(i,j) = saturate_cast<uchar>(image.at<uchar>(i,j) + 100);
						dst5.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);
				}
		}

		imshow("original image", image) , imshow("dst1 - bright", dst1);
		imshow("dst2 - darkness", dst2), imshow("dst3 - reversal", dst3);
		imshow("dst4 - brightness", dst4), imshow("dst5 - reversal", dst5);
		waitKey();

}
