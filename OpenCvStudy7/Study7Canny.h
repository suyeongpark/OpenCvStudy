#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study7Canny
{
public:
	Study7Canny();
	~Study7Canny();
	int Start();

private:
	void calc_direct(Mat Gy, Mat Gx, Mat& direct);
	void supp_nonMax(Mat sobel, Mat direct, Mat& dst);
	void trace(Mat max_so, Mat& pos_ck, Mat& hy_img, Point pt, int low);
	void hysteresis_th(Mat max_so, Mat& hy_img, int low, int high);

};

