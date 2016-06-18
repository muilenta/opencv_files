//This program displays multiple video feeds, each in a different window.
//Two camera devices are required for this (or emulated feeds).


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<stdio.h>
#include<stdlib.h>

using namespace cv;

void main()
{
	Mat image1;
	Mat image2;
	Mat image3;

	//cv capture pointer
	VideoCapture capture1;
	VideoCapture capture2;
	//VideoCapture capture3;  //uncomment this to display a third feed

	//open the img device
	capture1.open(0);
	capture2.open(1);
	//capture3.open(2);

	while (1)
	{
		//show the image from the webcam
		capture1 >> image1;
		imshow("window_1", image1);
		waitKey(10);

		capture2 >> image2;
		imshow("window_2", image2);
		waitKey(10);

		//capture3>>image3;
		//imshow("window_3",image3);
		//waitKey(10);
	}

}