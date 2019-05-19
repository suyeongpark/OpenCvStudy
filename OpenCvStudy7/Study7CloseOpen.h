#include <opencv2/opencv.hpp>
using namespace cv;

#pragma once
class Study7CloseOpen
{
public:
	Study7CloseOpen();
	~Study7CloseOpen();
	int Start();

private:
	bool check_match(Mat img, Point start, Mat mask, int mode = 0);
	void erosion(Mat img, Mat& dst, Mat mask);
	void dilation(Mat img, Mat& dst, Mat mask);
	void opening(Mat img, Mat& dst, Mat mask);
	void closing(Mat img, Mat& dst, Mat mask);
};

