#include "pch.h"
#include "Study7EdgeSobel.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study7EdgeSobel::Study7EdgeSobel()
{
}


Study7EdgeSobel::~Study7EdgeSobel()
{
}

int Study7EdgeSobel::Start()
{
	string path = "D:\\Dev\\Study\\Open CV ����ó��_�н��ڿ�\\���翹��\\07��_����\\07��_2��\\image\\";
	Mat image = imread(path + "edge_test1.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	float data1[] = {
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1,
	};

	float data2[] = {
		-1, -2, -1,
		0, 0, 0,
		1, 2, 1,
	};

	Mat dst, dst3, dst4;
	Differential(image, dst, data1, data2);

	Sobel(image, dst3, CV_32F, 1, 0, 3);
	Sobel(image, dst4, CV_32F, 0, 1, 3);
	convertScaleAbs(dst3, dst3);
	convertScaleAbs(dst4, dst4);

	imshow("image", image);
	imshow("�Һ� ����", dst);
	imshow("dst3-����_opencv", dst3);
	imshow("dst4-����_opencv", dst4);
	waitKey();

	return 0;
}

void Study7EdgeSobel::Differential(Mat image, Mat & dst, float data1[], float data2[])
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
