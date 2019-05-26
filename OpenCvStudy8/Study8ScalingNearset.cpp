#include "pch.h"
#include "Study8ScalingNearset.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study8ScalingNearset::Study8ScalingNearset()
{
}


Study8ScalingNearset::~Study8ScalingNearset()
{
}


int Study8ScalingNearset::Start()
{
	string path = "D:\\Dev\\Study\\Open CV ����ó��_�н��ڿ�\\���翹��\\08��_����\\08��_2~4��\\image\\";
	Mat image = imread(path + "interpolation_test.jpg", 0);
	CV_Assert(image.data);

	Mat dst1, dst2;
	scaling(image, dst1, Size(300, 300));
	scaling_nearest(image, dst2, Size(300, 300));

	imshow("image", image);
	imshow("dst1 - ��������", dst1);
	imshow("dst2 - �ֱ��� �̿�����", dst2);
	waitKey();

	return 0;
}

void Study8ScalingNearset::scaling(Mat img, Mat & dst, Size size)
{
	dst = Mat(size, img.type(), Scalar(0));
	double ratioX = (double)size.width / img.cols;
	double ratioY = (double)size.height / img.rows;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			int x = (int)(j * ratioX);
			int y = (int)(i * ratioY);
			dst.at<uchar>(y, x) = img.at<uchar>(i, j);
		}
	}
}

void Study8ScalingNearset::scaling_nearest(Mat img, Mat & dst, Size size)
{
	dst = Mat(size, CV_8U, Scalar(0));
	double ratioX = (double)size.width / img.cols;
	double ratioY = (double)size.height / img.rows;
	
	for (int i = 0; i < dst.rows - 1; i++)
	{
		for (int j = 0; j < dst.cols - 1; j++)
		{
			int x = (int)cvRound(j / ratioX);
			int y = (int)cvRound(i / ratioY);
			dst.at<uchar>(i, j) = img.at<uchar>(y, x);
		}
	}
}