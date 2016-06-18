//More drawing

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

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

	for (int i = 0; i< 100; i++) // 100 loops take around 10 seconds
	{
		//show the image from the webcam
		my_capture >> image1;

		//////////////// draw target, circle, text
		int x[10000];
		int y[10000];

		x[0] = i;
		y[0] = i;

		const int FRAME_WIDTH = 640;
		const int FRAME_HEIGHT = 480;
		putText(image1, "Hello World", Point(0, 200), 2, 1, Scalar(0, 0, 255), 2);
		//draw all points that have been found up to this point
		for (int k = 0; k < 100; k++)
		{
			circle(image1, Point(k, k), 20, Scalar(255, 0, 0), 2);
			//line(image1,Point(k,k),Point(k+10,k+10),Scalar(0,255,0),2);
		}
		for (int k = 0; k < 50; k++)
		{
			//circle(image1,Point(400-k,400-k),20,Scalar(0,255,0),2);
			line(image1, Point(200, 200 + k), Point(400, 400), Scalar(0, 255, 0), 2);
		}

		rectangle(image1, Point(330, 20), Point(280, 80), Scalar(255, 255, 0), 2, 8, 0);
		//waitKey(50);
		imshow("window_1", image1);
		waitKey(50);
	}


	getchar();

}







