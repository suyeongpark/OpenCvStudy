#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study9DFT
{
public:
	Study9DFT();
	~Study9DFT();
	int Start();

private:
	void log_mag(Mat complex_mat, Mat& dst);
	void shuffling(Mat mag_img, Mat& dst);
	Mat DFT_1D(Mat one_row, int dir);
	void DFT_2D(Mat complex_img, Mat& dst, int dir);
};

