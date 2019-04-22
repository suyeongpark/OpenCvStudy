#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#pragma once
class StudyReadCamera
{
public:
	StudyReadCamera();
	~StudyReadCamera();
	int Start();

private:
	void put_string(Mat& frame, string text, Point pt, int value);
};

