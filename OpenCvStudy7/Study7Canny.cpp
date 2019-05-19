#include "pch.h"
#include "Study7Canny.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study7Canny::Study7Canny()
{
}


Study7Canny::~Study7Canny()
{
}

int Study7Canny::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\07장_예제\\07장_2절\\image\\";
	Mat image = imread(path + "cannay_tset.jpg", 0);
	CV_Assert(image.data);

	Mat gau_img, Gx, Gy, direct, sobel, max_sobel, hy_img, canny;

	GaussianBlur(image, gau_img, Size(5, 5), 0.3);
	Sobel(gau_img, Gx, CV_32F, 1, 0, 3);
	Sobel(gau_img, Gy, CV_32F, 0, 1, 3);
	sobel = abs(Gx) + abs(Gy);

	calc_direct(Gy, Gx, direct);
	supp_nonMax(sobel, direct, max_sobel);
	hysteresis_th(max_sobel, hy_img, 100, 150);
	Canny(image, canny, 100, 150);

	imshow("image", image);
	imshow("canny", hy_img);
	imshow("opencv_canny", canny);
	waitKey();

	return 0;
}

void Study7Canny::calc_direct(Mat Gy, Mat Gx, Mat & direct)
{
	direct.create(Gy.size(), CV_8U);

	for (int i = 0; i < direct.rows; i++)
	{
		for (int j = 0; j < direct.cols; j++)
		{
			float gx = Gx.at<float>(i, j);
			float gy = Gy.at<float>(i, j);
			int theat = int(fastAtan2(gy, gx) / 45);
			direct.at<uchar>(i, j) = theat % 4;
		}
	}
}

void Study7Canny::supp_nonMax(Mat sobel, Mat direct, Mat & dst)
{
	dst = Mat(sobel.size(), CV_32F, Scalar(0));

	for (int i = 1; i < sobel.rows - 1; i++)
	{
		for (int j = 1; j < sobel.cols - 1; j++)
		{
			int dir = direct.at<uchar>(i, j);
			float v1, v2;

			if (dir == 0)
			{
				v1 = sobel.at<float>(i, j - 1);
				v2 = sobel.at<float>(i, j + 1);
			}
			else if (dir == 1)
			{
				v1 = sobel.at<float>(i + 1, j + 1);
				v2 = sobel.at<float>(i - 1, j - 1);
			}
			else if (dir == 2)
			{
				v1 = sobel.at<float>(i - 1, j);
				v2 = sobel.at<float>(i + 1, j);
			}
			else if (dir == 3)
			{
				v1 = sobel.at<float>(i + 1, j - 1);
				v2 = sobel.at<float>(i - 1, j + 1);
			}

			float center = sobel.at<float>(i, j);
			dst.at<float>(i, j) = (center > v1 && center > v2) ? center : 0;
		}
	}
}

void Study7Canny::trace(Mat max_so, Mat & pos_ck, Mat & hy_img, Point pt, int low)
{
	Rect rect(Point(0, 0), pos_ck.size());

	if (!rect.contains(pt))
		return;

	if (pos_ck.at<uchar>(pt) == 0 && max_so.at<float>(pt) > low)
	{
		pos_ck.at<uchar>(pt) = 1;
		hy_img.at<uchar>(pt) = 255;

		trace(max_so, pos_ck, hy_img, pt + Point(-1, -1), low);
		trace(max_so, pos_ck, hy_img, pt + Point(0, -1), low);
		trace(max_so, pos_ck, hy_img, pt + Point(1, -1), low);
		trace(max_so, pos_ck, hy_img, pt + Point(-1, 0), low);

		trace(max_so, pos_ck, hy_img, pt + Point(1, 0), low);
		trace(max_so, pos_ck, hy_img, pt + Point(-1, 1), low);
		trace(max_so, pos_ck, hy_img, pt + Point(0, 1), low);
		trace(max_so, pos_ck, hy_img, pt + Point(1, 1), low);
	}
}

void Study7Canny::hysteresis_th(Mat max_so, Mat & hy_img, int low, int high)
{
	Mat pos_ck(max_so.size(), CV_8U, Scalar(0));
	hy_img = Mat(max_so.size(), CV_8U, Scalar(0));

	for (int i = 0; i < max_so.rows; i++)
	{
		for (int j = 0; j < max_so.cols; j++)
		{
			if (max_so.at<float>(i, j) > high)
			{
				trace(max_so, pos_ck, hy_img, Point(j, i), low);
			}
		}
	}

}
