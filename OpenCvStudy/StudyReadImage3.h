#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#pragma once
class StudyReadImage3
{
public:
	StudyReadImage3();
	~StudyReadImage3();
	int Start();

private:
	void print_matInfo(string name, Mat img);
};

