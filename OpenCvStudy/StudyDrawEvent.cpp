#include "pch.h"
#include "StudyDrawEvent.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyDrawEvent::StudyDrawEvent()
{
}


StudyDrawEvent::~StudyDrawEvent()
{
}

string title3 = "이벤트 그리기";
Mat image3;
void onMouse3(int event, int x, int y, int flags, void* param);

int StudyDrawEvent::Start()
{
	image3 = Mat(300, 500, CV_8UC1, Scalar(255));
	imshow(title3, image3);
	setMouseCallback(title3, onMouse3, 0);
	waitKey(0);
	return 0;
}

void onMouse3(int event, int x, int y, int flags, void* param)
{
	static Point pt(-1, -1);

	if (event == EVENT_LBUTTONDOWN)
	{
		if (pt.x < 0)
		{
			pt = Point(x, y);
		}
		else
		{
			rectangle(image3, pt, Point(x, y), Scalar(50), 2);
			imshow(title3, image3);
			pt = Point(-1, -1);
		}
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		if (pt.x < 0)
		{
			pt = Point(x, y);
		}
		else
		{
			Point2d pt2 = pt - Point(x, y);
			int radius = (int)sqrt(pt2.x * pt2.x + pt2.y * pt2.y);
			circle(image3, pt, radius, Scalar(150), 2);
			imshow(title3, image3);
			pt = Point(-1, -1);
		}
	}


}