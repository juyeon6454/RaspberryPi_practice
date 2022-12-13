#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image(200,300,CV_8U,Scalar(255));
	namedWindow("keybord event", WINDOW_AUTOSIZE);
	imshow("keybord event", image);

	while(1)
	{
			int key = waitKey(100);
			if(key == 27) break;

			switch(key)
			{
				case 'a' : cout << "a key input" << endl; break;
				case 'b' : cout << "b key input" << endl; break;
				case 0x41 : cout << "A key input" << endl; break;
				case 66 : cout << "B key input" << endl; break;

				case 0x51 : cout << "left key input" << endl; break;
				case 0x52: cout << "top key input" << endl; break;
				case 0x53 : cout << "right key input" << endl; break;
				case 0x54 : cout << "under key input" << endl; break;
			}
	}
	return 0;
}

