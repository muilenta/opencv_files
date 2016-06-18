//Link to ceemple plugin that installs opencv dependencies: https://visualstudiogallery.msdn.microsoft.com/00ebd33e-c7c6-4a02-9466-b619b5eddfb5
//Ceemple link on google drive: https://drive.google.com/folderview?id=0Bw13WqGlAMkAfm45S05jOUVMUXJUcVo1T0FzSVUxTFNGSjVsa0hNN0lCekxjOFdxRFZONkU&usp=sharing
//opencv tutorials: http://docs.opencv.org/doc/tutorials/tutorials.html
//github repo: https://github.com/muilenta/
//highgui functions: http://www.ai.rug.nl/vakinformatie/pas/content/Highgui/opencvref_highgui.htm
//note: many sections of the code in these tutorials come from ceemple, opencv, or other sites.  Please help reference original authors if you know who they are.

//This program displays a picture.  You can pass in an image path to work with a differnet image if desired.

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	const char* filename = argc >= 2 ? argv[1] : "../images/baboon.jpg";  //if no image is passed in, use the baboon.png image
	//string filename = "../images/tony.png";  //another way to specify the image

	Mat image;
	image = imread(filename, CV_LOAD_IMAGE_COLOR);   // Read the file

	if (!image.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", image);                   // Show our image inside it.

	waitKey(0);                                          // Wait for a keystroke in the window
	return 0;
}