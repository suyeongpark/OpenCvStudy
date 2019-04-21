#include "pch.h"
#include "StudyTrackbarEvent2.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyTrackbarEvent2::StudyTrackbarEvent2()
{
}


StudyTrackbarEvent2::~StudyTrackbarEvent2()
{
}

string title2 = "¹à±âº¯°æ", bar_name = "¹à±â°ª";
Mat image2;
void onChange2(int value, void* userdata);
void onMouse2(int event, int x, int y, int flags, void* param);

int StudyTrackbarEvent2::Start()
{
	int value = 130;
	image2 = Mat(300, 500, CV_8UC1, Scalar(120));
	namedWindow(title2, WINDOW_AUTOSIZE);
	createTrackbar(bar_name, title2, &value, 255, onChange2);
	setMouseCallback(title2, onMouse2, 0);

	imshow(title2, image2);
	waitKey(0);
	return 0;
}

void onChange2(int value, void* userdata)
{

}

void onMouse2(int event, int x, int y, int flags, void* param)
{
	if (event == EVENT_RBUTTONDOWN)
	{
		add(image2, 10, image2);
		setTrackbarPos(bar_name, title2, image2.at<uchar>(0));
		imshow(title2, image2);
	}
	else if (event == EVENT_LBUTTONDOWN)
	{
		subtract(image2, 10, image2);
		setTrackbarPos(bar_name, title2, image2.at<uchar>(0));
		imshow(title2, image2);
	}
}
