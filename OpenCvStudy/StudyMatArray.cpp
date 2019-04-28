#include "pch.h"
#include "StudyMatArray.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyMatArray::StudyMatArray()
{
}


StudyMatArray::~StudyMatArray()
{
}

int StudyMatArray::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\05장_예제\\05장_1~2절\\image\\";
	Mat image = imread(path + "flip_test.jpg", IMREAD_COLOR);
	CV_Assert(image.data);

	Mat x_axis, y_axis, xy_axis, rep_img, trans_img;
	flip(image, x_axis, 0);
	flip(image, y_axis, 1);
	flip(image, xy_axis, -1);

	repeat(image, 1, 2, rep_img);
	transpose(image, trans_img);

	imshow("image", image);
	imshow("x_axis", x_axis);
	imshow("y_axis", y_axis);
	imshow("xy_axis", xy_axis);
	imshow("rep_img", rep_img);
	imshow("trans_img", trans_img);
	waitKey();

	return 0;
}
