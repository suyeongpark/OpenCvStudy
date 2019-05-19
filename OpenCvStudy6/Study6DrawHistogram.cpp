#include "pch.h"
#include "Study6DrawHistogram.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study6DrawHistogram::Study6DrawHistogram()
{
}


Study6DrawHistogram::~Study6DrawHistogram()
{
}

int Study6DrawHistogram::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\06장_예제\\06장_1절\\image\\";
	Mat image = imread(path + "pixel_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Mat hist, hist_img;
	calc_histo(image, hist, 256);
	draw_histo(hist, hist_img);

	imshow("image", image);
	imshow("hist_image", hist_img);
	waitKey();

	return 0;
}

void Study6DrawHistogram::calc_histo(const Mat & image, Mat & hist, int bins, int range_max)
{
	int histSize[] = { bins };
	float range[] = { 0, (float)range_max };
	int channels[] = { 0, };
	const float* ranges[] = { range };

	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}

void Study6DrawHistogram::draw_histo(Mat hist, Mat & hist_img, Size size)
{
	Mat temp_img = Mat(size, CV_8U, Scalar(255));
	float bin = (float)temp_img.cols / hist.rows;
	normalize(hist, hist, 0, temp_img.rows, NORM_MINMAX);

	for (int i = 0; i < hist.rows; i++)
	{
		float start_x = i * bin;
		float end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at<float>(i));

		if (pt2.y > 0)
		{
			rectangle(temp_img, pt1, pt2, Scalar(0), -1);
		}

		flip(temp_img, hist_img, 0);
	}
}


