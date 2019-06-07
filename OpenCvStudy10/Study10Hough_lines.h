#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study10Hough_lines
{
public:
	Study10Hough_lines();
	~Study10Hough_lines();
	int Start();

private:
	void hough_coord(Mat image, Mat& acc_mat, double rho, double theta);
	void acc_mask(Mat acc_mat, Mat& acc_dst, Size size, int thresh);
	void thres_lines(Mat acc_dst, Mat& lines, double _rho, double theta, int thresh);
	void sort_lines(Mat lines, vector<Vec2f>& s_lines);
	void houghLines(Mat src, vector<Vec2f>& s_lines, double rho, double theta, int thresh);
	void draw_houghLines(Mat src, Mat& dst, vector<Vec2f> lines, int nline);
};

