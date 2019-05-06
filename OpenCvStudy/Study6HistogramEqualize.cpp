#include "pch.h"
#include "Study6HistogramEqualize.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study6HistogramEqualize::Study6HistogramEqualize()
{
}


Study6HistogramEqualize::~Study6HistogramEqualize()
{
}

int Study6HistogramEqualize::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\06장_예제\\06장_4절\\image\\";
	Mat image = imread(path + "equalize_test.jpg", 0);
	CV_Assert(!image.empty());

	Mat hist, dst1, dst2, hist_img, hist_img1, hist_img2;
	create_hist(image, hist, hist_img);

	Mat accum_hist(Mat(hist.size(), hist.type(), Scalar(0)));
	accum_hist.at<float>(0) = hist.at<float>(0);

	for (int i = 1; i < hist.rows; i++)
	{
		accum_hist.at<float>(i) = accum_hist.at<float>(i - 1) + hist.at<float>(i);
	}

	accum_hist /= sum(hist)[0];
	accum_hist *= 255;
	dst1 = Mat(image.size(), CV_8U);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int idx = image.at<uchar>(i, j);
			dst1.at<uchar>(i, j) = (uchar)accum_hist.at<float>(idx);
		}
	}

	equalizeHist(image, dst2);
	create_hist(dst1, hist, hist_img1);
	create_hist(dst2, hist, hist_img2);

	imshow("image", image);
	imshow("hist_img", hist_img);
	imshow("dst1-User", dst1);
	imshow("User_hist", hist_img1);
	imshow("dst2-OpenCV", dst2);
	imshow("OpenCV_hist", hist_img2);

	waitKey();

	return 0;
}

void Study6HistogramEqualize::create_hist(Mat img, Mat& hist, Mat& hist_img)
{
	int histsize = 256, range = 256;
	calc_histo(img, hist, histsize, range);
	draw_histo(hist, hist_img);
}

void Study6HistogramEqualize::calc_histo(const Mat & image, Mat & hist, int bins, int range_max)
{
	int histSize[] = { bins };
	float range[] = { 0, (float)range_max };
	int channels[] = { 0, };
	const float* ranges[] = { range };

	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}

void Study6HistogramEqualize::draw_histo(Mat hist, Mat & hist_img, Size size)
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