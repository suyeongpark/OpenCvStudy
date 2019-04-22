#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#pragma once
class StudyReadImage
{
public:
	StudyReadImage();
	~StudyReadImage();
	int Start();

private:
	void print_matInfo(string name, Mat img);
};

