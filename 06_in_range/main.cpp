//This program converts the video feed to HSV, then filters out pixels based on high and low filter settings specified
#include "opencv2/opencv.hpp"

#include<stdio.h>
#include<stdlib.h>

using namespace cv;

void main()
{
	Mat image1;
	Mat hsv_image;
	Mat threshold_image;

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
		inRange(hsv_image, Scalar(30, 10, 45), Scalar(250, 256, 200), threshold_image); //values are 0 to 256
		imshow("window_3", threshold_image);
		waitKey(10);
	}

}






