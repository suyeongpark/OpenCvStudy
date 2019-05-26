#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study8Translation
{
public:
	Study8Translation();
	~Study8Translation();
	int Start();

private:
	void translation(Mat img, Mat& dst, Point pt);
};

