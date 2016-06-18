//this program demonstrates multiple threshold options.  Uncomment a few to try them out
//threshold tutorial: http://docs.opencv.org/trunk/doc/py_tutorials/py_imgproc/py_thresholding/py_thresholding.html

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

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
		//threshold(src, threshColor, 100, 200, THRESH_BINARY);
		//threshold(src, threshColor, 100, 200, THRESH_BINARY_INV);
		//threshold(src, threshColor, 100, 200, THRESH_TRUNC);
		threshold(src, threshColor, 100, 200, THRESH_TOZERO);
		//threshold(src, threshColor, 100, 200, THRESH_TOZERO_INV);
		cvtColor(src, srcGray, CV_BGR2GRAY);
		threshold(srcGray, threshGray, 100, 200, THRESH_BINARY);
		imshow("src", src);
		//imshow("src gray", srcGray);
		imshow("thresh color", threshColor);
		//imshow("thresh gray", threshGray);
		waitKey(10);
	}
}

