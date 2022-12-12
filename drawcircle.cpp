#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat image = Mat::zeros(300, 400, CV_8UC3);
	image.setTo(cv::Scalar(0,0,0) );


	Scalar color(0,0,255);
	Point p1(100, 100), p2(220, 100);
	Size size(50, 40);
	circle(image, p1, 50, color, -1);
	ellipse(image, p2, size,0 , 110, 270, color,10 );

	imshow("Draw Circle", image);
	waitKey(0);
	return 0;
}

