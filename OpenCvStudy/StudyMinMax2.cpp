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
	string path = "D:\\Dev\\Study\\Open CV ����ó��_�н��ڿ�\\���翹��\\05��_����\\05��_3~4��\\image\\";
	Mat image = imread(path + "minMax.jpg", IMREAD_GRAYSCALE);
	double minVal, maxVal;
	minMaxIdx(image, &minVal, &maxVal);

	double ratio = (maxVal - minVal) / 255.0;
	Mat dst = (image - minVal) / ratio;

	cout << "�ּڰ� = " << minVal << endl;
	cout << "�ִ� = " << maxVal << endl;

	imshow("image", image);
	imshow("dst", dst);
	waitKey();

	return 0;
}
