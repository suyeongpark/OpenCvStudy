#include "pch.h"
#include "Study7Edge_Dog.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study7Edge_Dog::Study7Edge_Dog()
{
}


Study7Edge_Dog::~Study7Edge_Dog()
{
}

int Study7Edge_Dog::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\07장_예제\\07장_2절\\image\\";
	Mat image = imread(path + "laplacian_test.jpg", 0);
	CV_Assert(image.data);

	double sigma = 1.4;
	Mat LoG_mask = GetLoGMask(Size(9, 9), sigma);

	Mat dst1, dst2, dst3, dst4, gaus_img;
	filter2D(image, dst1, -1, LoG_mask);
	GaussianBlur(image, gaus_img, Size(9, 9), sigma, sigma);
	Laplacian(gaus_img, dst2, -1, 5);

	GaussianBlur(image, dst3, Size(1, 1), 0.0);
	GaussianBlur(image, dst4, Size(9, 9), 1.6);
	Mat dst_DoG = dst3 - dst4;
	normalize(dst_DoG, dst_DoG, 0, 255, NORM_MINMAX);

	imshow("image", image);
	imshow("dst1 - log_filter2d", dst1);
	imshow("dst2 - log_opencv", dst2);
	imshow("dst_dog - dog_opencv", dst_DoG);
	waitKey();

	return 0;
}

Mat Study7Edge_Dog::GetLoGMask(Size size, double sigma)
{
	double ratio = 1 / (CV_PI * pow(sigma, 4.0));
	int center = size.height / 2;
	Mat dst(size, CV_64F);

	for (int i = 0; i < size.height; i++)
	{
		int y2 = (i - center) * (i - center);

		for (int j = 0; j < size.width; j++)
		{
			int x2 = (j - center) * (j - center);
			double value = (x2 + y2) / (2 * sigma * sigma);
			dst.at<double>(i, j) = -ratio * (1 - value) * exp(-value);
		}
	}

	double scale = (center * 10 / ratio);
	return dst * scale;
}
