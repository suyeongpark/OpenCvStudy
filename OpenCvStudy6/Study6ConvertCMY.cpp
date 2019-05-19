#include "pch.h"
#include "Study6ConvertCMY.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study6ConvertCMY::Study6ConvertCMY()
{
}


Study6ConvertCMY::~Study6ConvertCMY()
{
}

int Study6ConvertCMY::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\06장_예제\\06장_4절\\image\\";
	Mat image = imread(path + "color_model.jpg", IMREAD_COLOR);
	CV_Assert(!image.empty());

	Scalar white(255, 255, 255);
	Mat cmy_img = white - image;
	Mat cmy_arr[3];
	split(cmy_img, cmy_arr);

	imshow("BGR_img", image);
	imshow("CMY_img", cmy_img);
	imshow("Yellow", cmy_arr[0]);
	imshow("Magenta", cmy_arr[1]);
	imshow("Cyan", cmy_arr[2]);
	waitKey();
	return 0;
}
