#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study8AffineCombination
{
public:
	Study8AffineCombination();
	~Study8AffineCombination();
	int Start();

private:
	uchar bilinear_value(Mat img, double x, double y);
	void affine_tranform(Mat img, Mat& dst, Mat map, Size size);
	Mat getAffineMap(Point2d center, double dgree, double fx = 1, double fy = 1, Point2d translate = Point(0, 0));
};

