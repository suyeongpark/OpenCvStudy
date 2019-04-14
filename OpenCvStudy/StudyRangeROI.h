#include <string>
#include <opencv2/opencv.hpp>

class StudyRangeROI
{
public:
	StudyRangeROI();
	~StudyRangeROI();
	int Start();
	void print_locateROI(std::string str, cv::Mat m);
};

