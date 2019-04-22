#include "pch.h"
#include "StudyWriteImage.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyWriteImage::StudyWriteImage()
{
}


StudyWriteImage::~StudyWriteImage()
{
}

int StudyWriteImage::Start()
{
	string path = "D:\\Dev\\Study\\OpenCvStudy\\x64\\Debug\\image\\";

	Mat img8 = imread(path + "read_color.jpg", IMREAD_COLOR);
	CV_Assert(img8.data);

	vector<int> params_jpg, params_png;
	params_jpg.push_back(IMWRITE_JPEG_QUALITY);
	params_jpg.push_back(50);
	params_png.push_back(IMWRITE_PNG_COMPRESSION);
	params_png.push_back(90);

	imwrite(path + "write_test1.jpg", img8);
	imwrite(path + "write_test2.jpg", img8, params_jpg);
	imwrite(path + "write_test.png", img8, params_png);
	imwrite(path + "write_test.bmp", img8);

	waitKey(0);

	return 0;
}
