//display HSV 
//https://en.wikipedia.org/wiki/HSL_and_HSV

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include<stdio.h>
#include<stdlib.h>

using namespace cv;

void main()
{
	Mat image1;
	Mat hsv_image;

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
	}

}