#include "pch.h"
#include "StudyMinMax2.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyMinMax2::StudyMinMax2()
{
}


StudyMinMax2::~StudyMinMax2()
{
}

int StudyMinMax2::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\05장_예제\\05장_3~4절\\image\\";
	Mat image = imread(path + "minMax.jpg", IMREAD_GRAYSCALE);
	double minVal, maxVal;
	minMaxIdx(image, &minVal, &maxVal);

	double ratio = (maxVal - minVal) / 255.0;
	Mat dst = (image - minVal) / ratio;

	cout << "최솟값 = " << minVal << endl;
	cout << "최댓값 = " << maxVal << endl;

	imshow("image", image);
	imshow("dst", dst);
	waitKey();

	return 0;
}
