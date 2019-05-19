#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study7EdgePrewitt
{
public:
	Study7EdgePrewitt();
	~Study7EdgePrewitt();
	int Start();

private:
	void Differential(Mat image, Mat& dst, float data1[], float data2[]);
};

