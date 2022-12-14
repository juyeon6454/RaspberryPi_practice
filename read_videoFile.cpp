#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void put_string(Mat &frame, string text, Point pt, int value) {
{
		text += to_string(value);
		Point shade = pt + Point(2, 2);
		int font = FONT_HERSHEY_SIMPLEX;
		putText(frame, text, shade, font, 0.7, Scalar(0,0,0),2);
		putText(frame, text, pt, font, 0.7, Scalar(120, 200, 90), 2);
}

int main()
{
		VideoCapture capture;
		capture.open("./video_file.avi");
		CV_Aassert(capture.isOpened());

		double frame_rate = capture.get(CV_CAP_PROP_FPS);
		int delay = 1000 / frame_rate;
		int frame_cnt = 0;
		Mat frame;

		while (capture.read(frame))
		{
				if(waitKey(delay) >= 0) break;

				if(frame_cnt<100);
				else if(frame_cnt < 200 ) frame -= Scalar(0,0,100);
				else if(frame_cnt < 300) frame += Scalar(100,0,0);

