#include "pch.h"
#include "Study6ConvertHSV.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study6ConvertHSV::Study6ConvertHSV()
{
}


Study6ConvertHSV::~Study6ConvertHSV()
{
}

int Study6ConvertHSV::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\06장_예제\\06장_4절\\image\\";
	Mat image = imread(path + "color_space.jpg", IMREAD_COLOR);
	CV_Assert(!image.empty());

	Mat HSI_img, HSV_img, hsi[3], hsv[3];

	bgr2hsi(image, HSI_img);
	cvtColor(image, HSV_img, COLOR_BGR2HSV);
	split(HSI_img, hsi);
	split(HSV_img, hsv);

	imshow("BGR_Img", image);
	imshow("Hue", hsi[0]);
	imshow("Saturation", hsi[1]);
	imshow("Intensity", hsi[2]);
	imshow("OpenCV_Hue", hsv[0]);
	imshow("OpenCV_Saturation", hsv[1]);
	imshow("OpenCV_Value", hsv[2]);
	waitKey();
	return 0;
}

void Study6ConvertHSV::bgr2hsi(Mat img, Mat & hsi)
{
	hsi = Mat(img.size(), CV_32FC3);

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			float b = img.at<Vec3b>(i, j)[0];
			float g = img.at<Vec3b>(i, j)[1];
			float r = img.at<Vec3b>(i, j)[2];

			float s = 1 - 3 * min(r, min(g, b)) / (r + g + b);
			float v = (r + g + b) / 3.0f;

			float tmp1 = ((r - g) + (r - b)) * 0.5f;
			float tmp2 = sqrt((r - g) * (r - b) + (g - b) * (g - b));
			float angle = acos(tmp1 / tmp2) * (180.f / CV_PI);
			float h = (b <= g) ? angle : 360 - angle;

			hsi.at<Vec3f>(i, j) = Vec3f(h / 2, s * 255, v);
		}
	}

	hsi.convertTo(hsi, CV_8U);
}