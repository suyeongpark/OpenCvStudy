#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study7Dilation
{
public:
	Study7Dilation();
	~Study7Dilation();
	int Start();

private:
	bool check_match(Mat img, Point start, Mat mask, int mode = 0);
	void dilation(Mat img, Mat& dst, Mat mask);
};

