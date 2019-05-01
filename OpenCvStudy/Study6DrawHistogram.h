#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study6DrawHistogram
{
public:
	Study6DrawHistogram();
	~Study6DrawHistogram();
	int Start();

private:
	void calc_histo(const Mat& image, Mat& hist, int bins, int range_max = 256);
	void draw_histo(Mat hist, Mat& hist_img, Size size = Size(256, 200));
};

