#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study7EdgeSobel
{
public:
	Study7EdgeSobel();
	~Study7EdgeSobel();
	int Start();

private:
	void Differential(Mat image, Mat& dst, float data1[], float data2[]);
};

