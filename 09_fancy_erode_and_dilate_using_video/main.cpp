//erostion and dilation demonstrated using a video camera

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables
Mat src_img, erosion_dest, dilation_dest;

int erosion_ele = 0;
int eros_size = 0;
int dilation_ele = 0;
int dilation_size_ = 0;
int const max_elements = 2;
int const max_kernel_size_ = 21;

/** Function Headers */
void Erosion3(int, void*);
void Dilation3(int, void*);

/** @function main */
int main(int argc, char** argv)
{


	//cv capture pointer
	VideoCapture my_capture;

	//open the img device
	my_capture.open(0);

	//src_img = imread("..\\baboon.jpg");



	while (1)
	{
		my_capture >> src_img;
		/// Create windows
		namedWindow("Erosion Demo", CV_WINDOW_AUTOSIZE);
		namedWindow("Dilation Demo", CV_WINDOW_AUTOSIZE);
		cvMoveWindow("Dilation Demo", src_img.cols, 0);

		/// Create Erosion Trackbar
		createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
			&erosion_ele, max_elements,
			Erosion3);

		createTrackbar("Kernel size:\n 2n +1", "Erosion Demo",
			&eros_size, max_kernel_size_,
			Erosion3);

		/// Create Dilation Trackbar
		createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
			&dilation_ele, max_elements,
			Dilation3);

		createTrackbar("Kernel size:\n 2n +1", "Dilation Demo",
			&dilation_size_, max_kernel_size_,
			Dilation3);

		/// Default start
		Erosion3(0, 0);
		Dilation3(0, 0);
		waitKey(30);
	}
	//waitKey(500);
	my_capture.release();
	//return 0;
}

/**  @function Erosion  */
void Erosion3(int, void*)
{
	int erosion_type;
	if (erosion_ele == 0){ erosion_type = MORPH_RECT; }
	else if (erosion_ele == 1){ erosion_type = MORPH_CROSS; }
	else if (erosion_ele == 2) { erosion_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement(erosion_type,
		Size(2 * eros_size + 1, 2 * eros_size + 1),
		Point(eros_size, eros_size));

	/// Apply the erosion operation
	erode(src_img, erosion_dest, element);
	imshow("Erosion Demo", erosion_dest);
}

/** @function Dilation */
void Dilation3(int, void*)
{
	int dilation_type;
	if (dilation_ele == 0){ dilation_type = MORPH_RECT; }
	else if (dilation_ele == 1){ dilation_type = MORPH_CROSS; }
	else if (dilation_ele == 2) { dilation_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement(dilation_type,
		Size(2 * dilation_size_ + 1, 2 * dilation_size_ + 1),
		Point(dilation_size_, dilation_size_));
	/// Apply the dilation operation
	dilate(src_img, dilation_dest, element);
	imshow("Dilation Demo", dilation_dest);
}