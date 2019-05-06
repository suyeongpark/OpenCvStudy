#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study6HistogramEqualize
{
public:
	Study6HistogramEqualize();
	~Study6HistogramEqualize();
	int Start();

private:
	void calc_histo(const Mat& image, Mat& hist, int bins, int range_max = 256);
	void draw_histo(Mat hist, Mat& hist_img, Size size = Size(256, 200));
	void create_hist(Mat img, Mat& hist, Mat& hist_img);
};

