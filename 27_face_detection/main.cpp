#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	// capture from web camera init
	VideoCapture cap(0);
	cap.open(0);

	Mat img;

	// Load cascate classifier placed in sulution folder
	CascadeClassifier detector;
	string cascadeName = "../cascades/haarcascade_frontalface_alt.xml";
	bool loaded = detector.load(cascadeName);

	// Parameters of detectMultiscale Cascade Classifier

	int groundThreshold = 2;
	double scaleStep = 1.1;
	Size minimalObjectSize(80, 80);
	Size maximalObjectSize(200, 200);


	// Vector of returned faces
	vector<Rect> found;

	for (;;)
	{

		// Image from camera to Mat
		cap >> img;

		// Convert input to greyscale 
		Mat image_grey;
		cvtColor(img, image_grey, CV_BGR2GRAY);

		// why not
		found.clear();

		// Detect faces
		detector.detectMultiScale(image_grey, found, scaleStep, groundThreshold, 0 | 2, minimalObjectSize, maximalObjectSize);

		// Draw the results into mat retrieved from webcam
		if (found.size() > 0) {
			for (int i = 0; i <= found.size() - 1; i++) {

				rectangle(img, found[i].br(), found[i].tl(), Scalar(0, 0, 0), 1, 8, 0);

			}
		}

		//Show the results
		imshow("wooohooo", img);
		int key2 = waitKey(20);


	}


	return 0;
}