#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study7Difference_op
{
public:
	Study7Difference_op();
	~Study7Difference_op();
	int Start();

private:
	void DifferOp(Mat img, Mat& dst, int mask_size);
};

