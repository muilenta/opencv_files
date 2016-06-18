//this code demonstrates erosion and dilation to clean up noise in an image

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"#include<opencv\highgui.h>

#include<stdio.h>
#include<stdlib.h>

using namespace cv;

void on_trackbar2(int, void*) { } //called when trackbar is moved 

void main()
{
	Mat image1;
	Mat hsv_image;
	Mat threshold_image;
	Mat dialated_image;
	Mat eroded_image;

	int H_MIN = 20;  //0 to 256
	int H_MAX = 240;
	int S_MIN = 10;
	int S_MAX = 236;
	int V_MIN = 0;
	int V_MAX = 256;

	namedWindow("select colors", 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf(TrackbarName, "H_MIN", H_MIN);
	sprintf(TrackbarName, "H_MAX", H_MAX);
	sprintf(TrackbarName, "S_MIN", S_MIN);
	sprintf(TrackbarName, "S_MAX", S_MAX);
	sprintf(TrackbarName, "V_MIN", V_MIN);
	sprintf(TrackbarName, "V_MAX", V_MAX);

	createTrackbar("H_MIN", "select colors", &H_MIN, H_MAX, on_trackbar2);
	createTrackbar("H_MAX", "select colors", &H_MAX, H_MAX, on_trackbar2);
	createTrackbar("S_MIN", "select colors", &S_MIN, S_MAX, on_trackbar2);
	createTrackbar("S_MAX", "select colors", &S_MAX, S_MAX, on_trackbar2);
	createTrackbar("V_MIN", "select colors", &V_MIN, V_MAX, on_trackbar2);
	createTrackbar("V_MAX", "select colors", &V_MAX, V_MAX, on_trackbar2);

	//cv capture pointer
	VideoCapture tony_capture;

	//open the img device
	tony_capture.open(0);

	while (1)
	{
		//show the image from the webcam
		tony_capture >> hsv_image;


		(hsv_image, hsv_image, COLOR_BGR2HSV);

		tony_capture >> threshold_image;
		inRange(hsv_image, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold_image); //values are 0 to 256
		imshow("select_colors", threshold_image);
		waitKey(30);

		Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
		Mat dilateElement = getStructuringElement(MORPH_RECT, Size(3, 3));

		//erode and dialate twice each
		cv::erode(threshold_image, threshold_image, erodeElement);
		cv::erode(threshold_image, threshold_image, erodeElement);

		imshow("eroded image", threshold_image);

		cv::dilate(threshold_image, threshold_image, erodeElement);
		cv::dilate(threshold_image, threshold_image, erodeElement);

		imshow("dilated image", threshold_image);

	}

}

