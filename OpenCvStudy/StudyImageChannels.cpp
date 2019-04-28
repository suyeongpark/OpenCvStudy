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
	string path = "D:\\Dev\\Study\\Open CV ����ó��_�н��ڿ�\\���翹��\\05��_����\\05��_1~2��\\image\\";
	Mat image = imread(path + "color.jpg", IMREAD_COLOR);
	CV_Assert(image.data);

	Mat bgr[3];
	split(image, bgr);

	imshow("image", image);
	imshow("blue ä��", bgr[0]);
	imshow("green ä��", bgr[1]);
	imshow("red ä��", bgr[2]);
	waitKey();

	return 0;
}
