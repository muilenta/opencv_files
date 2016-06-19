//corner detection

//http://docs.opencv.org/doc/tutorials/features2d/trackingmotion/harris_detector/harris_detector.html
//http://opencvexamples.blogspot.com/2013/10/harris-corner-detection.html#.VEjZgDbn8kk
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int main()
{
	int thresh = 200;
	Mat src, gray;
	VideoCapture my_capture;

	//open the img device
	my_capture.open(0);

	while (1)
	{
		//show the image from the webcam
		my_capture >> src;

		cvtColor(src, gray, CV_BGR2GRAY);
		Mat dst, dst_norm, dst_norm_scaled;
		dst = Mat::zeros(src.size(), CV_32FC1);

		// Detecting corners
		cornerHarris(gray, dst, 7, 5, 0.05, BORDER_DEFAULT);

		// Normalizing
		normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
		convertScaleAbs(dst_norm, dst_norm_scaled);

		// Drawing a circle around corners
		for (int j = 0; j < dst_norm.rows; j++)
		{
			for (int i = 0; i < dst_norm.cols; i++)
			{
				if ((int)dst_norm.at<float>(j, i) > thresh)
				{
					circle(dst_norm_scaled, Point(i, j), 5, Scalar(0), 2, 8, 0);
				}
			}
		}

		// Showing the result
		namedWindow("corners_window", CV_WINDOW_AUTOSIZE);
		imshow("corners_window", dst_norm_scaled);
		waitKey(33);
	}
	return(0);
}
