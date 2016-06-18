//this program runs a simple threshold
//threshold tutorial: http://docs.opencv.org/trunk/doc/py_tutorials/py_imgproc/py_thresholding/py_thresholding.html

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;


/** @function main */
int main()
{
	Mat src; Mat srcGray;
	Mat threshColor, threshGray;
	int thresh = 100;
	int max_thresh = 255;
	VideoCapture myCapture;
	myCapture.open(0);


	while (1)
	{
		myCapture >> src;
		threshold(src, threshColor, 100, 200, THRESH_BINARY);
		cvtColor(src, srcGray, CV_BGR2GRAY);
		threshold(srcGray, threshGray, 100, 200, THRESH_BINARY);
		imshow("src", src);
		imshow("src gray", srcGray);
		imshow("thresh color", threshColor);
		imshow("thresh gray", threshGray);
		waitKey(10);
	}
}