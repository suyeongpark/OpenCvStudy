#include "pch.h"
#include "Study6ConvertOthers.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study6ConvertOthers::Study6ConvertOthers()
{
}


Study6ConvertOthers::~Study6ConvertOthers()
{
}

int Study6ConvertOthers::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\06장_예제\\06장_4절\\image\\";
	Mat image = imread(path + "color_space.jpg", IMREAD_COLOR);
	CV_Assert(!image.empty());

	Mat YCC_img, YUV_img, Lab_img, Gray_img;
	cvtColor(image, Gray_img, COLOR_BGR2GRAY);
	cvtColor(image, YCC_img, COLOR_BGR2YCrCb);
	cvtColor(image, YUV_img, COLOR_BGR2YUV);
	cvtColor(image, Lab_img, COLOR_BGR2Lab);

	Mat YCC_arr[3], YUV_arr[3], Lab_arr[3];
	split(YCC_img, YCC_arr);
	split(YUV_img, YUV_arr);
	split(Lab_img, Lab_arr);

	imshow("image", image);
	imshow("Gray_img", Gray_img);
	imshow("YCC_arr[0]-Y", YCC_arr[0]);
	imshow("YCC_arr[1]-Cr", YCC_arr[1]);
	imshow("YCC_arr[2]-Cv", YCC_arr[2]);
	imshow("YUV_img[0]-Y", YUV_arr[0]);
	imshow("YUV_img[1]-U", YUV_arr[1]);
	imshow("YUV_img[2]-V", YUV_arr[2]);
	imshow("Lab_arr[0]-L", Lab_arr[0]);
	imshow("Lab_arr[1]-a", Lab_arr[1]);
	imshow("Lab_arr[2]-b", Lab_arr[2]);
	waitKey();
	return 0;
}
