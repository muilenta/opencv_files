//Contour filtering with canny and sliders

#include <opencv2\highgui\highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#include <sstream>
#include <string>


#include <iostream>
#include <stdio.h>
#include <stdlib.h>


void my_trackbar19(int, void*){};
RNG rng19(12345);
/** @function main */
int main()
{
	Mat src, srcGray;
	VideoCapture myCapture;
	myCapture.open(0);
	Mat canny_output;

	int threshMin = 0;  //0 to 256
	int threshMax = 256;
	namedWindow("canny output", 0);
	char TrackbarName[50];
	sprintf(TrackbarName, "thresh min", threshMax);
	sprintf(TrackbarName, "thresh max", threshMax);

	createTrackbar("threshold min", "canny output", &threshMin, threshMax, my_trackbar19);
	createTrackbar("threshold max", "canny output", &threshMax, threshMax, my_trackbar19);

	while (1)
	{
		myCapture >> src;


		(src, srcGray, CV_BGR2GRAY);
		/// Detect edges using canny
		//Canny( srcGray, canny_output, 20, 220, 3 );
		Canny(src, canny_output, threshMin, threshMax, 3);

		imshow("canny output", canny_output);
		waitKey(20);

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		// Find contours
		findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));



		/// Draw contours

		Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
		for (int i = 0; i< contours.size(); i++)
		{
			Scalar 	color = Scalar(rng19.uniform(0, 255), rng19.uniform(0, 255), rng19.uniform(0, 255));
			drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		}
		namedWindow("Contours", CV_WINDOW_AUTOSIZE);
		imshow("Contours", drawing);
		waitKey(20);
	}

}
