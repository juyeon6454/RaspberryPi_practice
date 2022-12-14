#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
		Mat img8 = imread("../image/read_color.jpg", IMREAD_COLOR);
		CV_Assert(img8.data);
		Mat img16, img32;
		img8.convertTo(img16, CV_16U, 65535/255.0);
		img8.convertTo(img32, CV_32F, 1/255.0f);

		Rect roi(10, 10, 3, 3);
		cout << "img8 matrix part " << endl << img8(roi) << endl << endl;
		cout << "img16 matrix part " << endl << img16(roi) << endl << endl;
		cout << "img32 matrix part " << endl << img32(roi) << endl << endl;

		imwrite("../image/write_test_16.tif", img16);
		imwrite("../image/write_test_32.tif", img32);
		imshow("img16", img16);
		imshow("img32", img32);
		waitKey();
		return 0;
}
