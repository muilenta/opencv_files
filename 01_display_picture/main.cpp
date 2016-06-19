//Link to video tutorials: https://www.youtube.com/watch?v=Q6NkiY9fylw&list=PLpV2_Uaul7v_i88gZRwIwPgNGpakZnOhs
//Link to ceemple plugin that installs opencv dependencies: https://visualstudiogallery.msdn.microsoft.com/00ebd33e-c7c6-4a02-9466-b619b5eddfb5
//github repo: https://github.com/muilenta/
//note: many sections of the code in these tutorials come from ceemple, opencv, or other sites.  Please help reference original authors if you know who they are.

//highgui functions: http://www.ai.rug.nl/vakinformatie/pas/content/Highgui/opencvref_highgui.htm

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

	//load the image
	Mat image;
	image = imread(filename, CV_LOAD_IMAGE_COLOR);  
	//check if the image loaded properly
	if (!image.data){
		cout << "Image could not be loaded\n";
		return -1;
	}
	//show the image
	imshow("My Image", image);                 
	waitKey(0);                                       
	return 0;
}