//same as the previous program, but it displays the feed in two different windows

#include "opencv2/opencv.hpp"

#include<stdio.h>
#include<stdlib.h>

using namespace cv;

void main()
{
	Mat image1;
	Mat image2;

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

		my_capture >> image2;
		imshow("window_2", image2);
		waitKey(10);
	}

}