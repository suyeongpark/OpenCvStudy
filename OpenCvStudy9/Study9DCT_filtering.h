#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study9DCT_filtering
{
public:
	Study9DCT_filtering();
	~Study9DCT_filtering();
	int Start();

private:
	Mat DCT_block(Mat g);
	Mat IDCT_block(Mat f);
	Mat getDCT_filter_dc(int N, int M);
	Mat getDCT_filter_hori(int N, int M);
	Mat getDCT_filter_verti(int N, int M);
	Mat getDCT_filter_low(int N, int M);
	Mat getDCT_filter_high(int N, int M);
	void DCT_filtering(Mat img, Mat filter, Mat& dst, int N, int M);
};

