//track motion - get a difference image, threshold it, use erosion, draw a target at the center of the contours
//https://www.youtube.com/watch?v=X6rPdRZzgjg


#include <opencv2\highgui\highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//our sensitivity value to be used in the threshold() function
const static int SENSITIVITY_VALUE = 20;
//size of blur used to smooth the image to remove possible noise and
//increase the size of the object we are trying to track. (Much like dilate and erode)
const static int BLUR_SIZE = 10;
//we'll have just one object to search for
//and keep track of its position.
int liveObject17[2] = { 0, 0 };
//bounding rectangle of the object, we will use the center of this as its position.
Rect objectBoundingRectangle17 = Rect(0, 0, 0, 0);


//int to string helper function
string intToString_17(int number){

	//this function has a number input and string output
	std::stringstream ss;
	ss << number;
	return ss.str();
}

void searchForMovement17(Mat thresholdImage, Mat &cameraFeed){
	//notice how we use the '&' operator for the cameraFeed. This is because we wish
	//to take the values passed into the function and manipulate them, rather than just working with a copy.
	//eg. we draw to the cameraFeed in this function which is then displayed in the ma in() function.
	bool objectDetected = false;
	Mat temp;
	thresholdImage.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	//findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );// retrieves all contours
	findContours(temp, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);// retrieves external contours

	//if contours vector is not empty, we have found some objects
	if (contours.size()>0)objectDetected = true;
	else objectDetected = false;

	if (objectDetected){
		//the largest contour is found at the end of the contours vector
		//we will simply assume that the biggest contour is the object we are looking for.
		vector< vector<Point> > largestContourVec;
		largestContourVec.push_back(contours.at(contours.size() - 1));
		//make a bounding rectangle around the largest contour then find its centroid
		//this will be the object's final estimated position.
		objectBoundingRectangle17 = boundingRect(largestContourVec.at(0));
		int xpos = objectBoundingRectangle17.x + objectBoundingRectangle17.width / 2;
		int ypos = objectBoundingRectangle17.y + objectBoundingRectangle17.height / 2;

		imshow("tony test", thresholdImage);
		rectangle(cameraFeed, Point(xpos, ypos), Point(objectBoundingRectangle17.x + objectBoundingRectangle17.width, objectBoundingRectangle17.y + objectBoundingRectangle17.height), Scalar(255, 255, 0), 2, 8, 0);
		waitKey(100);
		//update the objects positions by changing the 'liveObject17' array values
		liveObject17[0] = xpos, liveObject17[1] = ypos;
	}
	//make some temp x and y variables so we dont have to type out so much
	int x = liveObject17[0];
	int y = liveObject17[1];
	//draw some crosshairs on the object
	circle(cameraFeed, Point(x, y), 20, Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);
	putText(cameraFeed, "Tracking object at (" + intToString_17(x) + "," + intToString_17(y) + ")", Point(x, y), 1, 1, Scalar(255, 0, 0), 2);
}
int main(){
	//some boolean variables for added functionality
	bool objectDetected = false;
	bool debugMode = true;
	bool trackingEnabled = true;
	Mat frame1, frame2;
	//their grayscale images (needed for absdiff() function)
	Mat grayImage1, grayImage2;
	//resulting difference image
	Mat differenceImage;
	//thresholded difference image (for use in findContours() function)
	Mat thresholdImage;
	//video capture object.
	VideoCapture capture;
	capture.open(0);
	while (1){
		//we can loop the video by re-opening the capture every time the video reaches its last frame
		//check if the video has reach its last frame.
		//we add '-1' because we are reading two frames from the video at a time.
		//if this is not included, we get a memory error!
		while (1){
			//read first frame
			capture >> (frame1);
			//convert frame1 to gray scale for frame differencing
			cvtColor(frame1, grayImage1, COLOR_BGR2GRAY);
			//copy second frame
			capture >> (frame2);
			//convert frame2 to gray scale for frame differencing
			cvtColor(frame2, grayImage2, COLOR_BGR2GRAY);
			//perform frame differencing with the sequential images. This will output an "intensity image"
			//do not confuse this with a threshold image, we will need to perform thresholding afterwards.
			absdiff(grayImage1, grayImage2, differenceImage);
			//threshold intensity image at a given sensitivity value
			threshold(differenceImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);
			if (debugMode == true){
				//show the difference image and threshold image
				imshow("Difference Image", differenceImage);
				imshow("Threshold Image", thresholdImage);
			}
			else{
				//if not in debug mode, destroy the windows so we don't see them anymore
				destroyWindow("Difference Image");
				destroyWindow("Threshold Image");

			}
			//use blur() to smooth the image, remove possible noise and
			//increase the size of the object we are trying to track. (Much like dilate and erode)
			blur(thresholdImage, thresholdImage, Size(10, 10));
			//threshold again to obtain binary image from blur output
			threshold(thresholdImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);
			if (debugMode == true){
				//show the threshold image after it's been "blurred"
				imshow("final thresh image", thresholdImage);
			}
			else {
				//if not in debug mode, destroy the windows so we don't see them anymore
				destroyWindow("final thresh image");
			}

			//if tracking enabled, search for contours in our thresholded image
			if (trackingEnabled){

				searchForMovement17(thresholdImage, frame1);
			}
			//show our captured frame
			imshow("Frame1", frame1);
			//check to see if a button has been pressed.
			//this 10ms delay is necessary for proper operation of this program
			//if removed, frames will not have enough time to referesh and a blank 
			//image will appear.

			waitKey(20);


		}
		//release the capture before re-opening and looping again.
		capture.release();
	}

	return 0;

}