#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study6ConvertHSV
{
public:
	Study6ConvertHSV();
	~Study6ConvertHSV();
	int Start();

private:
	void bgr2hsi(Mat img, Mat& hsi);
};

