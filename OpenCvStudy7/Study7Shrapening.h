#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study7Shrapening
{
public:
	Study7Shrapening();
	~Study7Shrapening();
	int Start();

private:
	void Filter(Mat img, Mat& dst, Mat mask);
};

