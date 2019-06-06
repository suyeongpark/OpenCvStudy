#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study9Remove_Moire
{
public:
	Study9Remove_Moire();
	~Study9Remove_Moire();
	int Start();

private:
	void log_mag(Mat complex_mat, Mat& dst);
	void shuffling(Mat mag_img, Mat& dst);
	Mat scramble(Mat signal);
	Mat zeropadding(Mat img);
	void butterfly(Mat& dst, int dir);
	void FFT_2D(Mat complex_img, Mat& dst, int dir);
	void FFT(Mat image, Mat& dft_coef, Mat& dft_img);
	Mat IFFT(Mat dft_coef, Size size);
};

