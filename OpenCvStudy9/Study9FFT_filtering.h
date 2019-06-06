#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study9FFT_filtering
{
public:
	Study9FFT_filtering();
	~Study9FFT_filtering();
	int Start();

private:
	void log_mag(Mat complex_mat, Mat& dst);
	void shuffling(Mat mag_img, Mat& dst);
	Mat scramble(Mat signal);
	Mat zeropadding(Mat img);
	void butterfly(Mat& dst, int dir);
	void FFT_2D(Mat complex_img, Mat& dst, int dir);
	Mat get_lowpassFilter(Size size, int radius);
	Mat get_highpassFilter(Size size, int radius);
	void FFT(Mat image, Mat& dft_coef, Mat& dft_img);
	Mat IFFT(Mat dft_coef, Size size);
};

