#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study6HueHistogram
{
public:
	Study6HueHistogram();
	~Study6HueHistogram();
	int Start();

private:
	void calc_histo(const Mat& image, Mat& hist, int bins, int range_max = 256);
	void draw_histo_hue(Mat hist, Mat& hist_img, Size size = Size(256, 200));
	Mat make_palatte(int rows);
};

