#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study7Blurring
{
public:
	Study7Blurring();
	~Study7Blurring();
	int Start();

private:
	void Filter(Mat img, Mat& dst, Mat mask);
};

