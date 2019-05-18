#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study7Homogenity_op
{
public:
	Study7Homogenity_op();
	~Study7Homogenity_op();
	int Start();

private:
	void HomogenOp(Mat img, Mat& dst, int mask_size);
};

