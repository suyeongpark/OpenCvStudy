#include "pch.h"
#include "Study7CloseOpen.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study7CloseOpen::Study7CloseOpen()
{
}


Study7CloseOpen::~Study7CloseOpen()
{
}

int Study7CloseOpen::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\07장_예제\\07장_4절\\image\\";
	Mat image = imread(path + "morph_test1.jpg", 0);
	CV_Assert(image.data);

	Mat th_img, dst1, dst2, dst3, dst4;
	threshold(image, th_img, 128, 255, THRESH_BINARY);
	
	Matx<uchar, 3, 3> mask;
	mask << 0, 1, 0,
		1, 1, 1,
		0, 1, 1;

	opening(th_img, dst1, (Mat)mask);
	closing(th_img, dst2, (Mat)mask);
	morphologyEx(th_img, dst3, MORPH_OPEN, mask);
	morphologyEx(th_img, dst4, MORPH_CLOSE, mask);

	imshow("image", image);
	imshow("User_Opening", dst1);
	imshow("User_Closing", dst2);
	imshow("OpenCV_Opening", dst3);
	imshow("OpenCV_Closing", dst4);
	waitKey();

	return 0;
}

bool Study7CloseOpen::check_match(Mat img, Point start, Mat mask, int mode)
{
	for (int u = 0; u < mask.rows; u++)
	{
		for (int v = 0; v < mask.cols; v++)
		{
			Point pt(v, u);
			int m = mask.at<uchar>(pt);
			int p = img.at<uchar>(start + pt);

			bool ch = (p == 255);

			if (m == 1 && ch == mode)
				return false;
		}
	}

	return true;
}

void Study7CloseOpen::erosion(Mat img, Mat & dst, Mat mask)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));

	if (mask.empty())
		mask = Mat(3, 3, CV_8UC1, Scalar(1));

	Point h_m = mask.size() / 2;

	for (int i = h_m.y; i < img.rows - h_m.y; i++)
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			Point start = Point(j, i) - h_m;
			bool check = check_match(img, start, mask, 0);
			dst.at<uchar>(i, j) = (check) ? 255 : 0;
		}
	}
}

void Study7CloseOpen::dilation(Mat img, Mat & dst, Mat mask)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));

	if (mask.empty())
		mask = Mat(3, 3, CV_8UC1, Scalar(0));

	Point h_m = mask.size() / 2;


	for (int i = h_m.y; i < img.rows - h_m.y; i++)
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			Point start = Point(j, i) - h_m;
			bool check = check_match(img, start, mask, 0);
			dst.at<uchar>(i, j) = (check) ? 0 : 255;
		}
	}
}

void Study7CloseOpen::opening(Mat img, Mat & dst, Mat mask)
{
	Mat tmp;
	erosion(img, tmp, mask);
	dilation(tmp, dst, mask);
}

void Study7CloseOpen::closing(Mat img, Mat & dst, Mat mask)
{
	Mat tmp;
	dilation(img, tmp, mask);
	erosion(tmp, dst, mask);
}
