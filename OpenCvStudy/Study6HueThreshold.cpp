#include "pch.h"
#include "Study6HueThreshold.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Mat hue;
Range th(50, 100);

void OnThresHold(int value, void* userdata);

Study6HueThreshold::Study6HueThreshold()
{
}


Study6HueThreshold::~Study6HueThreshold()
{
}

int Study6HueThreshold::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\06장_예제\\06장_4절\\image\\";
	Mat image = imread(path + "color_space.jpg", IMREAD_COLOR);
	CV_Assert(!image.empty());

	Mat HSV, hsv[3];
	cvtColor(image, HSV, COLOR_BGR2HSV);
	split(HSV, hsv);
	hsv[0].copyTo(hue);

	namedWindow("result", WINDOW_AUTOSIZE);
	createTrackbar("Hue_th1", "result", &th.start, 255, OnThresHold);
	createTrackbar("Hue_th2", "result", &th.end, 255, OnThresHold);

	//OnThresHold();
	imshow("image", image);
	waitKey();

	return 0;
}

void OnThresHold(int value, void* userdata)
{
	Mat result = Mat(hue.size(), CV_8U, Scalar(0));

	for (int i = 0; i < result.rows; i++)
	{
		for (int j = 0; j < result.cols; j++)
		{
			bool ck = hue.at<uchar>(i, j) >= th.start && hue.at<uchar>(i, j) < th.end;
			result.at<uchar>(i, j) = (ck) ? 255 : 0;
		}
	}

	imshow("result", result);
}
