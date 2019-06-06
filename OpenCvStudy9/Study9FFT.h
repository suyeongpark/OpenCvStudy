#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study9FFT
{
public:
	Study9FFT();
	~Study9FFT();
	int Start();

private:
	void log_mag(Mat complex_mat, Mat& dst);
	void shuffling(Mat mag_img, Mat& dst);
	Mat scramble(Mat signal);
	Mat zeropadding(Mat img);
	void butterfly(Mat& dst, int dir);
	void FFT_2D(Mat complex_img, Mat& dst, int dir);
};

