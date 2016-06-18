//This program allows the user to move sliders to change threshold values

#include "opencv2/opencv.hpp"


using namespace cv;

void my_trackbar(int, void*) { } //called when trackbar is moved 

void main()
{
	Mat image1;
	Mat hsv_image;
	Mat threshold_image;

	int H_MIN = 0;  //0 to 256
	int H_MAX = 256;
	int S_MIN = 0;
	int S_MAX = 256;
	int V_MIN = 0;
	int V_MAX = 256;

	namedWindow("select colors", 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf(TrackbarName, "H_MIN", H_MIN);
	sprintf(TrackbarName, "H_MAX", H_MAX);
	sprintf(TrackbarName, "S_MIN", S_MIN);
	sprintf(TrackbarName, "S_MAX", S_MAX);
	sprintf(TrackbarName, "V_MIN", V_MIN);
	sprintf(TrackbarName, "V_MAX", V_MAX);

	createTrackbar("H_MIN", "select colors", &H_MIN, H_MAX, my_trackbar);
	createTrackbar("H_MAX", "select colors", &H_MAX, H_MAX, my_trackbar);
	createTrackbar("S_MIN", "select colors", &S_MIN, S_MAX, my_trackbar);
	createTrackbar("S_MAX", "select colors", &S_MAX, S_MAX, my_trackbar);
	createTrackbar("V_MIN", "select colors", &V_MIN, V_MAX, my_trackbar);
	createTrackbar("V_MAX", "select colors", &V_MAX, V_MAX, my_trackbar);

	//cv capture pointer
	VideoCapture my_capture;

	//open the img device
	my_capture.open(0);

	while (1)
	{
		//show the image from the webcam
		my_capture >> image1;
		imshow("window_1", image1);
		waitKey(10);

		my_capture >> hsv_image;
		cvtColor(hsv_image, hsv_image, COLOR_BGR2HSV);
		imshow("window_2", hsv_image);
		waitKey(10);

		my_capture >> threshold_image;
		inRange(hsv_image, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold_image); //values are 0 to 256
		imshow("select_colors", threshold_image);
		waitKey(10);
	}

}






