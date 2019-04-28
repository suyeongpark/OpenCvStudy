#include "pch.h"
#include "StudySmAvg.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudySmAvg::StudySmAvg()
{
}


StudySmAvg::~StudySmAvg()
{
}

int StudySmAvg::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\05장_예제\\05장_5~6절\\image\\";
	Mat image = imread(path + "sum_test.jpg", 1);
	CV_Assert(image.data);
	Mat mask(image.size(), CV_8U, Scalar(0)), meanMat, stddevMat;
	mask(Rect(20, 40, 70, 70)).setTo(255);

	Scalar sum_value = sum(image);
	Scalar mean_value1 = mean(image);
	Scalar mean_value2 = mean(image, mask);

	cout << "[sum_value] = " << sum_value << endl;
	cout << "[meam_value1] = " << mean_value1 << endl;
	cout << "[meam_value2] = " << mean_value2 << endl;

	meanStdDev(image, meanMat, stddevMat);
	cout << "[mean] = " << meanMat << endl;
	cout << "[stddev] = " << stddevMat << endl;

	meanStdDev(image, meanMat, stddevMat, mask);
	cout << "[mean] = " << meanMat << endl;
	cout << "[stddev] = " << stddevMat << endl;

	imshow("image", image);
	imshow("mask", mask);
	waitKey();

	return 0;
}
