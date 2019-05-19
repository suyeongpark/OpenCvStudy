#include "pch.h"
#include "Study7Blurring.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study7Blurring::Study7Blurring()
{
}


Study7Blurring::~Study7Blurring()
{
}

int Study7Blurring::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\07장_예제\\07장_1절\\image\\";
	Mat image = imread(path + "filter_blur.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	float data[] = {
		1 / 9.f, 1 / 9.f, 1 / 9.f,
		1 / 9.f, 1 / 9.f, 1 / 9.f,
		1 / 9.f, 1 / 9.f, 1 / 9.f,
	};

	Mat mask(3, 3, CV_32F, data);
	Mat blur;
	Filter(image, blur, mask);
	blur.convertTo(blur, CV_8U);

	imshow("image", image);
	imshow("blur", blur);
	waitKey();

	return 0;
}

void Study7Blurring::Filter(Mat img, Mat & dst, Mat mask)
{
	dst = Mat(img.size(), CV_32F, Scalar(0));
	Point h_m = mask.size() / 2;

	for (int i = h_m.y; i < img.rows - h_m.y; i++)
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			float sum = 0;

			for (int u = 0; u < mask.rows; u++)
			{
				for (int v = 0; v < mask.cols; v++)
				{
					int y = i + u - h_m.y;
					int x = j + v - h_m.x;
					sum += mask.at<float>(u, v) * img.at<uchar>(y, x);
				}
			}

			dst.at<float>(i, j) = sum;
		}
	}
}