#include "pch.h"
#include "Study7EdgePrewitt.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study7EdgePrewitt::Study7EdgePrewitt()
{
}


Study7EdgePrewitt::~Study7EdgePrewitt()
{
}

int Study7EdgePrewitt::Start()
{
	string path = "D:\\Dev\\Study\\Open CV ����ó��_�н��ڿ�\\���翹��\\07��_����\\07��_2��\\image\\";
	Mat image = imread(path + "edge_test1.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	float data1[] = {
		-1, 0, 1,
		-1, 0, 1,
		-1, 0, 1,
	};

	float data2[] = {
		-1, -1, -1,
		0, 0, 0,
		1, 1, 1,
	};

	Mat dst;
	Differential(image, dst, data1, data2);

	imshow("image", image);
	imshow("������ ����", dst);
	waitKey();

	return 0;
}

void Study7EdgePrewitt::Differential(Mat image, Mat & dst, float data1[], float data2[])
{
	Mat dst1, mask1(3, 3, CV_32F, data1);
	Mat dst2, mask2(3, 3, CV_32F, data1);

	filter2D(image, dst1, CV_32F, mask1);
	filter2D(image, dst2, CV_32F, mask2);
	magnitude(dst1, dst2, dst);
	dst.convertTo(dst, CV_8U);

	convertScaleAbs(dst1, dst1);
	convertScaleAbs(dst2, dst2);

	imshow("dst1 - ���� ����ũ", dst1);
	imshow("dst2 - ���� ����ũ", dst2);
}
