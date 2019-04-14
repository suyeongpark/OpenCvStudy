#include "pch.h"
#include "StudyRange.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

StudyRange::StudyRange()
{
}


StudyRange::~StudyRange()
{
}


int StudyRange::Start()
{
	Range r1(0, 3), r2(3, 7);
	int data[] =
	{
		10, 11, 12, 13, 14, 15, 16,
		20, 21, 22, 23, 24, 25, 26,
		30, 31, 32, 33, 34, 35, 36,
		40, 41, 42, 43, 44, 45, 46,
	};

	Mat m1, m2;
	m1 = Mat(4, 7, CV_32S, data);
	m2 = m1(r1, r2);

	cout << "[m1�� 2�� ��] = " << m1.row(2) << endl;
	cout << "[m1�� 1�� ��] = " << m1.col(1) << endl;
	cout << "[m1�� (0~2��)] = " << m1.rowRange(r1) << endl;

	cout << "[m1] = " << m1 << endl;
	cout << "[m1 (0~2, 3~6)] = " << m2 << endl;

	m2.setTo(50);

	cout << "[m1] = " << m1 << endl;
	cout << "[m2] = " << m2 << endl;

	return 0;
}
