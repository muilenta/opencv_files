
//This program displays video from device 0

#include "opencv2\opencv.hpp"
using namespace cv;
int main()
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened()) // check if we succeeded
		return -1;
	Mat edges;

	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		imshow("Feed", frame);
		if (waitKey(30) >= 0)
			break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}