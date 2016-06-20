#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

#include<cmath>

int main(int argc, char** argv)
{
	Mat image;
	Size goalSize = Size(140, 140);
	//const std::string& directoryPath = "";
	Mat resized;
	Size originalSize = image.size();
	//float ratio = static_cast<float>(goalSize.height) / originalSize.height; 
	//Size newSize((int)(originalSize.width * ratio), (int)(originalSize.height * ratio));

	//Mat clipRect;

	const char* filename = argc >= 2 ? argv[1] : "../images/baboon.jpg";

	image = imread(filename, CV_LOAD_IMAGE_COLOR);   // Read the file
	if (!image.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", image);                   // Show our image inside it.

	resize(image, resized, goalSize);
	imshow("resized window", resized);

	Rect clipRect(100, 100, 200, 200);//  goalSize.width, resized.size().height);
	//Rect clipRect()
	Mat croppedRect = image(clipRect);
	//resized = resized(clipRect);
	imshow("clipped window", croppedRect);

	string my_string;
	string my_number = "1";

	imwrite("..\\images\\image.jpg", croppedRect);
	waitKey(0);                                          // Wait for a keystroke in the window
	return 0;
	;
}
