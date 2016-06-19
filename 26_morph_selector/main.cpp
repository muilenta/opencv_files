//apply different types of morphs to the video stream using sliders

//http://docs.opencv.org/doc/tutorials/imgproc/opening_closing_hats/opening_closing_hats.html

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables
Mat morph_src, morph_dst;

int live_morph_elem = 0;
int live_morph_size = 0;
int live_morph_operator = 0;
int const live_max_operator = 4;
int const live_max_elem = 2;
int const live_max_kernel_size = 21;

char* live_window_name = "Morphology Transformations Demo";

/** Function Headers */
void Morphology_Operations3(int, void*);

/** @function main */
int main()
{
	//cv capture pointer
	VideoCapture my_capture;

	//open the img device
	my_capture.open(0);

	while (1)
	{
		//show the image from the webcam
		my_capture >> morph_src;
		
		if (!morph_src.data)
			return -1;

		/// Create window
		namedWindow(live_window_name, CV_WINDOW_AUTOSIZE);

		/// Create Trackbar to select Morphology operation
		createTrackbar("Operator:\n 0: Opening - 1: Closing \n 2: Gradient - 3: Top Hat \n 4: Black Hat", live_window_name, &live_morph_operator, live_max_operator, Morphology_Operations3);

		/// Create Trackbar to select kernel type
		createTrackbar("Element:\n 0: Rect - 1: Cross - 2: Ellipse", live_window_name,
			&live_morph_elem, live_max_elem,
			Morphology_Operations3);

		/// Create Trackbar to choose kernel size
		createTrackbar("Kernel size:\n 2n +1", live_window_name,
			&live_morph_size, live_max_kernel_size,
			Morphology_Operations3);

		/// Default start
		Morphology_Operations3(0, 0);

		waitKey(20);
		//return 0;
	}
}

/**
* @function Morphology_Operations
*/
void Morphology_Operations3(int, void*)
{
	// Since MORPH_X : 2,3,4,5 and 6
	int operation = live_morph_operator + 2;

	Mat element = getStructuringElement(live_morph_elem, Size(2 * live_morph_size + 1, 2 * live_morph_size + 1), Point(live_morph_size, live_morph_size));

	/// Apply the specified morphology operation
	morphologyEx(morph_src, morph_dst, operation, element);
	imshow(live_window_name, morph_dst);
}