#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study8AffineTransform
{
public:
	Study8AffineTransform();
	~Study8AffineTransform();
	int Start();

private:
	uchar bilinear_value(Mat img, double x, double y);
	void affine_tranform(Mat img, Mat& dst, Mat map, Size size);
};

