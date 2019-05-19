#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study6HistogramStretching
{
public:
	Study6HistogramStretching();
	~Study6HistogramStretching();
	int Start();

private:
	void calc_histo(const Mat& image, Mat& hist, int bins, int range_max = 256);
	void draw_histo(Mat hist, Mat& hist_img, Size size = Size(256, 200));
	int search_valueIdx(Mat hist, int bias = 0);
};

