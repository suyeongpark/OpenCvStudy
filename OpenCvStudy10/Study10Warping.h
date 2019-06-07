#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study10Warping
{
public:
	Study10Warping();
	~Study10Warping();
	int Start();

private:
	void morphing();
	void onMouse(int event, int x, int y, int flags, void* param);
};

