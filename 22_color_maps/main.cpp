//this program cycles through the different color maps - autumn, cool, jet, etc.

//http://docs.opencv.org/trunk/modules/contrib/doc/facerec/colormaps.html

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <iostream>

using namespace cv;

int main(int argc, const char *argv[]) {
	//const char* filename = argc >= 2 ? argv[1] : "../images/baboon.jpg";  //uncomment to use an image passed in
	String filename = "../images/maui.jpg";

	if (!filename.empty()) {
		Mat img0 = imread(filename);
		// Throw an exception, if the image can't be read:
		if (img0.empty()) {
			CV_Error(CV_StsBadArg, "Failed to load image");
		}
		// Holds the colormap version of the image:
		Mat cm_img0;
		// Apply the colormap:
		for (int i = 0; i < 12; i++){
			applyColorMap(img0, cm_img0, i);
			// Show the result:
			imshow("cm_img0", cm_img0);
			waitKey(1500);
		}
	}
	return 0;
}

/*  Colormaps
COLORMAP_AUTUMN = 0,
COLORMAP_BONE = 1,
COLORMAP_JET = 2,
COLORMAP_WINTER = 3,
COLORMAP_RAINBOW = 4,
COLORMAP_OCEAN = 5,
COLORMAP_SUMMER = 6,
COLORMAP_SPRING = 7,
COLORMAP_COOL = 8,
COLORMAP_HSV = 9,
COLORMAP_PINK = 10,
COLORMAP_HOT = 11

*/