#include <string>
#include <opencv2/opencv.hpp>

#pragma once
class StudyMatPush
{
public:
	StudyMatPush();
	~StudyMatPush();
	int Start();
	void print_matInfo(std::string str, cv::Mat m);
};

