#include "pch.h"
#include "Study8ScalingBilinear.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study8ScalingBilinear::Study8ScalingBilinear()
{
}


Study8ScalingBilinear::~Study8ScalingBilinear()
{
}


int Study8ScalingBilinear::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\08장_예제\\08장_2~4절\\image\\";
	Mat image = imread(path + "interpolation_test.jpg", 0);
	CV_Assert(image.data);

	Mat dst1, dst2, dst3, dst4;
	scaling_bilinear(image, dst1, Size(300, 300));
	scaling_nearest(image, dst2, Size(300, 300));
	resize(image, dst3, Size(300, 300), 0, 0, INTER_LINEAR);
	resize(image, dst4, Size(300, 300), 0, 0, INTER_NEAREST);

	imshow("image", image);
	imshow("dst1 - 양선형", dst1);
	imshow("dst2 - 최근접 이웃보간", dst2);
	imshow("dst3 - opencv 양선형", dst3);
	imshow("dst4 - opencv 최근접 이웃보간", dst4);
	waitKey();

	return 0;
}

void Study8ScalingBilinear::scaling_nearest(Mat img, Mat & dst, Size size)
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

uchar Study8ScalingBilinear::bilinear_value(Mat img, double x, double y)
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

void Study8ScalingBilinear::scaling_bilinear(Mat img, Mat & dst, Size size)
{
	dst = Mat(size, img.type(), Scalar(0));
	double ratio_y = (double)size.height / img.rows;
	double ratio_x = (double)size.width / img.cols;

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			double y = i / ratio_y;
			double x = j / ratio_x;
			dst.at<uchar>(i, j) = bilinear_value(img, x, y);
		}
	}
}
