#include "pch.h"
#include "StudyWriteImage2.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyWriteImage2::StudyWriteImage2()
{
}


StudyWriteImage2::~StudyWriteImage2()
{
}

int StudyWriteImage2::Start()
{
	string path = "D:\\Dev\\Study\\OpenCvStudy\\x64\\Debug\\image\\";

	Mat img8 = imread(path + "read_color.jpg", IMREAD_COLOR);
	CV_Assert(img8.data);

	Mat img16, img32;
	img8.convertTo(img16, CV_16U, 65535 / 255.0);
	img8.convertTo(img32, CV_32F, 1 / 255.0f);

	Rect roi(10, 10, 3, 3);
	cout << "img8 青纺狼 老何 " << endl << img8(roi) << endl << endl;
	cout << "img16 青纺狼 老何 " << endl << img16(roi) << endl << endl;
	cout << "img32 青纺狼 老何 " << endl << img32(roi) << endl << endl;

	imwrite(path + "write_test_16.tif", img8);
	imwrite(path + "write_test_32.tif", img32);

	imshow("img16", img16);
	imshow("img32", img32);

	waitKey(0);

	return 0;
}
