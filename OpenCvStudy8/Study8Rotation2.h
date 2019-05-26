#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study8Rotation2
{
public:
	Study8Rotation2();
	~Study8Rotation2();
	int Start();

private:
	uchar bilinear_value(Mat img, double x, double y);
	void rotation(Mat img, Mat& dst, double dgree, Point pt);
	float calc_angle(Point pt[3]);
};

