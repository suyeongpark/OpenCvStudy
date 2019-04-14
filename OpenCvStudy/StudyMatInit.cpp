#include "pch.h"
#include "StudyMatInit.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

StudyMatInit::StudyMatInit()
{
}


StudyMatInit::~StudyMatInit()
{
}

int StudyMatInit::Start()
{
	// 1
	//Mat m1 = Mat::ones(3, 5, CV_8UC1);
	//Mat m2 = Mat::zeros(3, 5, CV_8UC1);
	//Mat m3 = Mat::eye(3, 5, CV_8UC1);

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;
	//cout << "[m3] = " << endl << m3 << endl;

	// 2
	//double a = 32.12345678, b = 2.7;
	//short c = 400;
	//float d = 10.f, e = 11.f, f = 13.f;

	//Mat_<int> m1(2, 4);
	//Mat_<uchar> m2(3, 4, 100);
	//Mat_<short> m3(4, 5, c);

	//m1 << 1, 2, 3, 4, 5, 6;
	//Mat m4 = (Mat_<double>(2, 3) << 1, 2, 3, 4, 5, 6);
	//Mat m5 = (Mat_<float>(2, 3) << a, b, c, d, e, f);

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;
	//cout << "[m3] = " << endl << m3 << endl;
	//cout << "[m4] = " << endl << m4 << endl;
	//cout << "[m5] = " << endl << m5 << endl;

	// 3
	Matx<int, 3, 3> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
	Matx<float, 2, 3> m2(1, 2, 3, 4, 5, 6);
	Matx<double, 3, 5> m3(3, 4, 5, 7);

	Matx23d m4(3, 4, 5, 6, 7, 8);
	Matx34d m5(1, 2, 3, 10, 11, 12, 13, 14, 15);
	Matx66d m6(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

	cout << "m5(0, 0) = " << m5(0, 0) << " m5(1, 0) = " << m5(1, 0) << endl;
	cout << "m6(0, 1) = " << m6(0, 1) << " m6(1, 3) = " << m6(1, 3) << endl;

	cout << "[m1] = " << endl << m1 << endl;
	cout << "[m5] = " << endl << m5 << endl;
	cout << "[m6] = " << endl << m6 << endl;

	return 0;
}