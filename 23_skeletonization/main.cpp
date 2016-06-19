//this program things the image until only a skeleton representation is left.  

//http://opencv-code.com/quick-tips/implementation-of-thinning-algorithm-in-opencv/

/**
* Code for thinning a binary image using Zhang-Suen algorithm.
*/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
/**
* Perform one thinning iteration.
* Normally you wouldn't call this function directly from your code.
*
* @param  im    Binary image with range = 0-1
* @param  iter  0=even, 1=odd
*/
void thinningIteration(Mat& im, int iter)
{
	Mat marker = Mat::zeros(im.size(), CV_8UC1);

	for (int i = 1; i < im.rows - 1; i++)
	{
		for (int j = 1; j < im.cols - 1; j++)
		{
			uchar p2 = im.at<uchar>(i - 1, j);
			uchar p3 = im.at<uchar>(i - 1, j + 1);
			uchar p4 = im.at<uchar>(i, j + 1);
			uchar p5 = im.at<uchar>(i + 1, j + 1);
			uchar p6 = im.at<uchar>(i + 1, j);
			uchar p7 = im.at<uchar>(i + 1, j - 1);
			uchar p8 = im.at<uchar>(i, j - 1);
			uchar p9 = im.at<uchar>(i - 1, j - 1);

			int A = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) +
				(p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
				(p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
				(p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
			int B = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
			int m1 = iter == 0 ? (p2 * p4 * p6) : (p2 * p4 * p8);
			int m2 = iter == 0 ? (p4 * p6 * p8) : (p2 * p6 * p8);

			if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
				marker.at<uchar>(i, j) = 1;
		}
	}

	im &= ~marker;
}

/**
* Function for thinning the given binary image
*
* @param  im  Binary image with range = 0-255
*/
void thinning(Mat& im, int i)
{
	im /= 255;

	Mat prev = Mat::zeros(im.size(), CV_8UC1);
	Mat diff;

	do {
		thinningIteration(im, 0);
		thinningIteration(im, 1);
		absdiff(im, prev, diff);
		im.copyTo(prev);
	} while (countNonZero(diff) > i * 10000);  

	im *= 255;
}

/**
* This is an example on how to call the thinning function above.
*/
int main()
{
	//Mat src = imread("../images/horse.jpg");
	Mat src = imread("../images/person.jpg");
	if (src.empty())
		return -1;

	Mat bw;
	cvtColor(src, bw, CV_BGR2GRAY);
	threshold(bw, bw, 10, 255, CV_THRESH_BINARY);

	//show the original image
	imshow("src", src);

	//loop through, thin, and show the image (note, remove this loop, and set the 10k value above to zero to have the algo finish quickly)
	for (int i = 1; i < 40; i++)
	{
		thinning(bw, i);
		imshow("dst", bw);
		waitKey(40);
	}

	imshow("dst", bw);
	waitKey(0);

	return 0;
}