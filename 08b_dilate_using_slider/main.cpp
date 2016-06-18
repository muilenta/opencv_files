//Dilation example.  Use the slider to increase the impact

#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

#include<iostream>

using namespace std;
using namespace cv;

int ksize = 1;
void on_trackbar(int, void*);
void createTrackbars();

int main(void)
{
	createTrackbars();
	on_trackbar(0, 0);
	Mat frame, dilateimg;
	frame = imread("../images/baboon.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//chess.JPG"
	cvtColor(frame, frame, CV_BGR2GRAY);
	while (waitKey(30) != 27)
	{
		dilate(frame, dilateimg, getStructuringElement(MORPH_RECT, Size(ksize, ksize)));
		imshow("Image", dilateimg);
	}
}

void createTrackbars()
{
	namedWindow("Image", WINDOW_NORMAL);//create window trackbarwindow
	createTrackbar("dilate me", "Image", &ksize, 255, on_trackbar);
}


void on_trackbar(int, void*)
{//This function gets called whenever a
	// trackbar position is changed
	if (ksize == 0)
	{
		ksize = 1;
	}
	cout << ksize << endl;







}