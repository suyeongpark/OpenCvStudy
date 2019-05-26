#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study8ScalingNearset
{
public:
	Study8ScalingNearset();
	~Study8ScalingNearset();
	int Start();

private:
	void scaling(Mat img, Mat& dst, Size size);
	void scaling_nearest(Mat img, Mat& dst, Size size);
};

