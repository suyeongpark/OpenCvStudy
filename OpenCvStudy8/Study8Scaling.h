#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study8Scaling
{
public:
	Study8Scaling();
	~Study8Scaling();
	int Start();

private:
	void scaling(Mat img, Mat& dst, Size size);
};

