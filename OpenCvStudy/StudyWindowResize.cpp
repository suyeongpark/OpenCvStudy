#include "pch.h"
#include "StudyWindowResize.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyWindowResize::StudyWindowResize()
{
}


StudyWindowResize::~StudyWindowResize()
{
}

int StudyWindowResize::Start()
{
	Mat image(300, 400, CV_8U, Scalar(255));
	string title1 = "창 크기변경 1- AUTOSIZE";
	string title2 = "창 크기변경 2- NORMAL";

	namedWindow(title1, WINDOW_AUTOSIZE);
	namedWindow(title2, WINDOW_NORMAL);
	resizeWindow(title1, 500, 200);
	resizeWindow(title2, 500, 200);

	imshow(title1, image);
	imshow(title2, image);

	waitKey();

	return 0;
}
