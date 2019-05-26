#include "pch.h"
#include "Study8Rotation.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study8Rotation::Study8Rotation()
{
}


Study8Rotation::~Study8Rotation()
{
}

int Study8Rotation::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\08장_예제\\08장_5~7절\\image\\";
	Mat image = imread(path + "rotate_test.jpg", 0);
	CV_Assert(image.data);

	Mat dst1, dst2;
	Point center = image.size() / 2;
	rotation(image, dst1, 20);
	rotation(image, dst2, 20, center);

	imshow("image", image);
	imshow("dst1 - 원점 회전", dst1);
	imshow("dst2 - 중심점 회전", dst2);
	waitKey();

	return 0;
}

void Study8Rotation::rotation(Mat img, Mat & dst, double dgree)
{
	double radian = dgree / 180 * CV_PI;
	double sin_value = sin(radian);
	double cos_value = cos(radian);

	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			double x = j * cos_value + i * sin_value;
			double y = -j * sin_value + i * cos_value;

			if (rect.contains(Point2d(x, y)))
				dst.at<uchar>(i, j) = bilinear_value(img, x, y);
		}
	}
}

void Study8Rotation::rotation(Mat img, Mat & dst, double dgree, Point pt)
{
	double radian = dgree / 180 * CV_PI;
	double sin_value = sin(radian);
	double cos_value = cos(radian);

	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			int jj = j - pt.x;
			int ii = i - pt.y;
			double x = jj * cos_value + ii * sin_value + pt.x;
			double y = -jj * sin_value + ii * cos_value + pt.y;

			if (rect.contains(Point2d(x, y)))
				dst.at<uchar>(i, j) = bilinear_value(img, x, y);
		}
	}
}

uchar Study8Rotation::bilinear_value(Mat img, double x, double y)
{
	if (x >= img.cols - 1)
		x--;

	if (y >= img.rows - 1)
		y--;

	Point pt((int)x, (int)y);
	int A = img.at<uchar>(pt);
	int B = img.at<uchar>(pt + Point(0, 1));
	int C = img.at<uchar>(pt + Point(1, 0));
	int D = img.at<uchar>(pt + Point(1, 1));

	double alpha = y - pt.y;
	double beta = x - pt.x;
	int M1 = A + (int)cvRound(alpha * (B - A));
	int M2 = C + (int)cvRound(alpha * (D - C));
	int P = M1 + (int)cvRound(beta * (M2 - M1));

	return saturate_cast<uchar>(P);
}
