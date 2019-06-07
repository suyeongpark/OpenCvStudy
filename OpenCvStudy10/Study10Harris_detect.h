#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study10Harris_detect
{
public:
	Study10Harris_detect();
	~Study10Harris_detect();
	int Start();

private:
	void cornerharris(Mat image, Mat& corner, int bSize, int kSize, float k);
	Mat draw_corner(Mat corner, Mat image, int thresh);
	void cornerHarris_demo(int )
};

