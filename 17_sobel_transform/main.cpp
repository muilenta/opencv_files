//This program applies the sobel transform on a video feed
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>

#include<stdio.h>
#include<stdlib.h>

using namespace cv;

int main()
{
	Mat my_image, blur_image;
	Mat gray_image;
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	Mat grad;

	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	//cv capture pointer
	VideoCapture my_capture;

	//open the img device
	my_capture.open(0);

	//loop through, apply the sobel transform to each image captured, and display it
	while (1)
	{
		Mat src, src_gray;
		my_capture.read(src);

		Mat grad;
		const char* window_name = "Sobel Demo - Simple Edge Detector";
		int scale = 1;
		int delta = 0;
		int ddepth = CV_16S;

		if (src.empty())
		{
			return -1;
		}
		GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
		cvtColor(src, src_gray, COLOR_RGB2GRAY);
		namedWindow(window_name, WINDOW_AUTOSIZE);
		Mat grad_x, grad_y;
		Mat abs_grad_x, abs_grad_y;
		Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
		convertScaleAbs(grad_x, abs_grad_x);
		Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
		convertScaleAbs(grad_y, abs_grad_y);
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

		imshow("my_window", grad);
		waitKey(33);
	}

}
