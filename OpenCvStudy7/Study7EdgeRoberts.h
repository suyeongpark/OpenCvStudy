#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study7EdgeRoberts
{
public:
	Study7EdgeRoberts();
	~Study7EdgeRoberts();
	int Start();

private:
	void Filter(Mat img, Mat& dst, Mat mask);
	void Differential(Mat image, Mat& dst, float data1[], float data2[]);
};

