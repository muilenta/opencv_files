//Tracking blue, or another color if the threshold sliders are changed after running

#include <opencv2\highgui\highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



//https://www.youtube.com/watch?v=bSeFrPrqZ2A

#include <sstream>
#include <string>


using namespace cv;
using std::vector;
//trackbars
int H_MIN13_2 = 74;
int H_MAX13_2 = 158;
int S_MIN13_2 = 100;
int S_MAX13_2 = 256;
int V_MIN13_2 = 95;
int V_MAX13_2 = 203;

void my_trackbars(int, void*) {// called when trackbars are instantiated
}

void createTrackbars(){
	//create window for trackbars
	namedWindow("trackbars", 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf(TrackbarName, "H_MIN", H_MIN13_2);
	sprintf(TrackbarName, "H_MAX", H_MAX13_2);
	sprintf(TrackbarName, "S_MIN", S_MIN13_2);
	sprintf(TrackbarName, "S_MAX", S_MAX13_2);
	sprintf(TrackbarName, "V_MIN", V_MIN13_2);
	sprintf(TrackbarName, "V_MAX", V_MAX13_2);
	//create trackbars and insert them into window        
	createTrackbar("H_MIN", "trackbars", &H_MIN13_2, H_MAX13_2, my_trackbars);
	createTrackbar("H_MAX", "trackbars", &H_MAX13_2, H_MAX13_2, my_trackbars);
	createTrackbar("S_MIN", "trackbars", &S_MIN13_2, S_MAX13_2, my_trackbars);
	createTrackbar("S_MAX", "trackbars", &S_MAX13_2, S_MAX13_2, my_trackbars);
	createTrackbar("V_MIN", "trackbars", &V_MIN13_2, V_MAX13_2, my_trackbars);
	createTrackbar("V_MAX", "trackbars", &V_MAX13_2, V_MAX13_2, my_trackbars);
}

void track_object(int &color, int &x, int &y, Mat threshold, Mat &cameraFeed){
	Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();  //if this is big, we have a noisy image
		for (int index = 0; index >= 0; index = hierarchy[index][0]) {
			Moments moment = moments((cv::Mat)contours[index]);
			double area = moment.m00; //area
			x = moment.m10 / area;
			y = moment.m01 / area;
			objectFound = true;
			refArea = area;
		}
		//let user know you found an object
		if (objectFound == true){
			putText(cameraFeed, "Tracking Object", Point(0, 50), 2, 1, Scalar(0, 255, 0), 2);
			//draw object location on screen			
			circle(cameraFeed, Point(x, y), 10, Scalar(0, 255, 0), 2);
			printf("Color %d position: x = %d, y = %d, \n", color, x, y);
		}
	}
}

int main()
{
	Mat cameraFeed;
	Mat HSV;
	Mat threshold;
	Mat green_threshold;
	//x and y values for the location of the object
	int bx = 0, by = 0; //blue x and y
	int gx = 0, gy = 0; //green x and y
	int color = 0;
	createTrackbars();
	VideoCapture capture;
	capture.open(0);

	int i;
	while (1){    //100 iterations should take round 10 seconds
		capture.read(cameraFeed);
		//convert frame from BGR to HSV colorspace
		cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
		//filter and store in threshold matrix
		//blue
		inRange(HSV, Scalar(H_MIN13_2, S_MIN13_2, V_MIN13_2), Scalar(H_MAX13_2, S_MAX13_2, V_MAX13_2), threshold);
		//erode and dilate to clean up the image
		Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
		Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));
		erode(threshold, threshold, erodeElement);
		dilate(threshold, threshold, dilateElement);
		//track the object
		color = 1;
		track_object(color, bx, by, threshold, cameraFeed);
		//printf("blue position x = %d, y = %d, \n", x ,y);

		imshow("blue_threshold", threshold);
		imshow("camera_feed", cameraFeed);

		waitKey(30);
	}
}
