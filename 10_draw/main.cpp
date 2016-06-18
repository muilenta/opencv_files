//Draw a crosshair, some text, and a chess piece over the video feed

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include<stdio.h>
#include<stdlib.h>

using namespace cv;

void MyPolygon(Mat);

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

		//////////////// draw target, circle, text
		int x = 100;
		int y = 100;
		const int FRAME_WIDTH = 640;
		const int FRAME_HEIGHT = 480;
		putText(image1, "Crosshair", Point(0, 50), 2, 1, Scalar(0, 255, 0), 2);

		circle(image1, Point(x, y), 20, Scalar(0, 255, 0), 2);
		line(image1, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
		line(image1, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
		line(image1, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
		line(image1, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);


		imshow("window_1", image1);

		MyPolygon(image1);

		waitKey(30);
		imshow("window 2", image1);
		waitKey(30);
	}

}


void MyPolygon(Mat img)
{
	int lineType = 8;
	int w = 100;

	// Create some points
	Point rook_points[1][20];
	rook_points[0][0] = Point(w / 4.0, 7 * w / 8.0);
	rook_points[0][1] = Point(3 * w / 4.0, 7 * w / 8.0);
	rook_points[0][2] = Point(3 * w / 4.0, 13 * w / 16.0);
	rook_points[0][3] = Point(11 * w / 16.0, 13 * w / 16.0);
	rook_points[0][4] = Point(19 * w / 32.0, 3 * w / 8.0);
	rook_points[0][5] = Point(3 * w / 4.0, 3 * w / 8.0);
	rook_points[0][6] = Point(3 * w / 4.0, w / 8.0);
	rook_points[0][7] = Point(26 * w / 40.0, w / 8.0);
	rook_points[0][8] = Point(26 * w / 40.0, w / 4.0);
	rook_points[0][9] = Point(22 * w / 40.0, w / 4.0);
	rook_points[0][10] = Point(22 * w / 40.0, w / 8.0);
	rook_points[0][11] = Point(18 * w / 40.0, w / 8.0);
	rook_points[0][12] = Point(18 * w / 40.0, w / 4.0);
	rook_points[0][13] = Point(14 * w / 40.0, w / 4.0);
	rook_points[0][14] = Point(14 * w / 40.0, w / 8.0);
	rook_points[0][15] = Point(w / 4.0, w / 8.0);
	rook_points[0][16] = Point(w / 4.0, 3 * w / 8.0);
	rook_points[0][17] = Point(13 * w / 32.0, 3 * w / 8.0);
	rook_points[0][18] = Point(5 * w / 16.0, 13 * w / 16.0);
	rook_points[0][19] = Point(w / 4.0, 13 * w / 16.0);

	const Point* ppt[1] = { rook_points[0] };
	int npt[] = { 20 };

	fillPoly(img,
		ppt,
		npt,
		1,
		Scalar(255, 255, 255),
		lineType);
}

