//create hough lines, and superimpose on the video feed

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src;
	VideoCapture myCapture;
	myCapture.open(0);
	Mat dst, cdst;

	while (1)
	{
		myCapture >> src;
		Canny(src, dst, 20, 200, 3);
		cvtColor(dst, cdst, CV_GRAY2BGR);
		vector<Vec4i> lines;
		HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);
		for (size_t i = 0; i < lines.size(); i++)
		{
			Vec4i l = lines[i];
			line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
		}
		imshow("source", src);
		imshow("detected lines", cdst);
		waitKey(10);
	}
	return 0;
}
