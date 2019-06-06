#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study9DCT
{
public:
	Study9DCT();
	~Study9DCT();
	int Start();

private:
	Mat DCT_block(Mat g);
	Mat IDCT_block(Mat f);
	void DCT_2D(Mat img, Mat& dst, int N, int M, int dir);
};

