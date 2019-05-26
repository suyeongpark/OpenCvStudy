#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study8ScalingBilinear
{
public:
	Study8ScalingBilinear();
	~Study8ScalingBilinear();
	int Start();

private:
	void scaling_nearest(Mat img, Mat& dst, Size size);
	uchar bilinear_value(Mat img, double x, double y);
	void scaling_bilinear(Mat img, Mat& dst, Size size);
};

