#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study8Rotation
{
public:
	Study8Rotation();
	~Study8Rotation();
	int Start();

private:
	uchar bilinear_value(Mat img, double x, double y);
	void rotation(Mat img, Mat& dst, double dgree);
	void rotation(Mat img, Mat& dst, double dgree, Point pt);
};

