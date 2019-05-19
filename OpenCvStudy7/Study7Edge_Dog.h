#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study7Edge_Dog
{
public:
	Study7Edge_Dog();
	~Study7Edge_Dog();
	int Start();

private:
	Mat GetLoGMask(Size size, double sigma);
};

