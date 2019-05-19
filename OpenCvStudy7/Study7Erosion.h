#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study7Erosion
{
public:
	Study7Erosion();
	~Study7Erosion();
	int Start();

private:
	bool check_match(Mat img, Point start, Mat mask, int mode = 0);
	void erosion(Mat img, Mat& dst, Mat mask);
};

