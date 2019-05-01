#include "pch.h"
#include "Study6HueHistogram.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study6HueHistogram::Study6HueHistogram()
{
}


Study6HueHistogram::~Study6HueHistogram()
{
}

int Study6HueHistogram::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\06장_예제\\06장_3절\\image\\";
	Mat image = imread(path + "hue_hist.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Mat HSV_img, HSV_arr[3];

	// 책의 예제대로 하는데 안된다. 물론 아래로도 안 됨.
	cvtColor(image, HSV_img, COLOR_YUV2BGR_NV21);
	split(HSV_img, HSV_arr);

	Mat hue_hist, hue_hist_img;
	calc_histo(HSV_arr[0], hue_hist, 18, 180);
	draw_histo_hue(hue_hist, hue_hist_img, Size(360, 200));

	imshow("image", image);
	imshow("Hue_hist_image", hue_hist_img);
	waitKey();


	return 0;
}

void Study6HueHistogram::calc_histo(const Mat & image, Mat & hist, int bins, int range_max)
{
	int histSize[] = { bins };
	float range[] = { 0, (float)range_max };
	int channels[] = { 0, };
	const float* ranges[] = { range };

	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}

void Study6HueHistogram::draw_histo_hue(Mat hist, Mat & hist_img, Size size)
{
	Mat hsv_palatte = make_palatte(hist.rows);

	hist_img = Mat(size, CV_8UC3, Scalar(255, 255, 255));
	float bin = (float)hist_img.cols / hist.rows;
	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);

	for (int i = 0; i < hist.rows; i++)
	{
		float start_x = (i * bin);
		float end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at<float>(i));

		Scalar color = hsv_palatte.at<Vec3b>(i);
		
		if (pt2.y > 0)
		{
			rectangle(hist_img, pt1, pt2, color, -1);
		}

		flip(hist_img, hist_img, 0);
	}
}

Mat Study6HueHistogram::make_palatte(int rows)
{
	Mat hsv(rows, 1, CV_8UC3);

	for (int i = 0; i < rows; i++)
	{
		uchar hue = saturate_cast<uchar>((float)i / rows * 180);
		hsv.at<Vec3b>(i) = Vec3b(hue, 255, 255);
	}

	// 책의 예제대로 하는데 안된다. 물론 아래로도 안 됨.
	cvtColor(hsv, hsv, COLOR_YUV2BGR_NV21);
	return hsv;
}
