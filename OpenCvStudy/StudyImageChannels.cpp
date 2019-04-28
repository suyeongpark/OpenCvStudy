#include "pch.h"
#include "StudyImageChannels.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyImageChannels::StudyImageChannels()
{
}


StudyImageChannels::~StudyImageChannels()
{
}

int StudyImageChannels::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\05장_예제\\05장_1~2절\\image\\";
	Mat image = imread(path + "color.jpg", IMREAD_COLOR);
	CV_Assert(image.data);

	Mat bgr[3];
	split(image, bgr);

	imshow("image", image);
	imshow("blue 채널", bgr[0]);
	imshow("green 채널", bgr[1]);
	imshow("red 채널", bgr[2]);
	waitKey();

	return 0;
}
