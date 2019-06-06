#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study9DCT_fast
{
public:
	Study9DCT_fast();
	~Study9DCT_fast();
	int Start();

private:
	Mat calc_cosine(int N, int M);
	Mat DCT_block(Mat g);
	Mat DCT_block(Mat g, Mat cos_mat, int dir);
	Mat IDCT_block(Mat f);
	void DCT_2D(Mat img, Mat& dst, int N, int M, int dir);
	void DCT_2D_fast(Mat img, Mat& dst, int N, int M, int dir);
};

