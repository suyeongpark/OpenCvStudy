#include "pch.h"
#include "Study7Erosion.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study7Erosion::Study7Erosion()
{
}


Study7Erosion::~Study7Erosion()
{
}

int Study7Erosion::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\07장_예제\\07장_4절\\image\\";
	Mat image = imread(path + "morph_test1.jpg", 0);
	CV_Assert(image.data);

	Mat th_img, dst1, dst2;
	threshold(image, th_img, 128, 255, THRESH_BINARY);

	uchar data[] = {
		0, 1, 0,
		1, 1, 1,
		0, 1, 0,
	};

	Mat mask(3, 3, CV_8UC1, data);

	erosion(th_img, dst1, (Mat)mask);
	morphologyEx(th_img, dst2, MORPH_ERODE, mask);

	imshow("image", image);
	imshow("이진 영상", th_img);
	imshow("User_dilation", dst1);
	imshow("OpenCV_dilatoin", dst2);
	waitKey();

	return 0;
}

bool Study7Erosion::check_match(Mat img, Point start, Mat mask, int mode)
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

void Study7Erosion::erosion(Mat img, Mat & dst, Mat mask)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));

	if (mask.empty())
		mask = Mat(3, 3, CV_8UC1, Scalar(1));

	Point h_m = mask.size() / 2;

	for (int i = h_m.y; i < img.rows - h_m.y; i++)
	{
		for (int j = h_m.x; j < img.cols- h_m.x; j++)
		{
			Point start = Point(j, i) - h_m;
			bool check = check_match(img, start, mask, 0);
			dst.at<uchar>(i, j) = (check) ? 255 : 0;
		}
	}
}
