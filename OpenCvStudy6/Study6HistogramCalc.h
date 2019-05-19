#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study6HistogramCalc
{
public:
	Study6HistogramCalc();
	~Study6HistogramCalc();
	int Start();

private:
	//void calc_histo(Mat image, Mat& hist, int bins, int range_max = 256);
	void calc_histo(const Mat& image, Mat& hist, int bins, int range_max = 256);
};

