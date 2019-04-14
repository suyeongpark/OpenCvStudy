#include "pch.h"
#include "StudyMatSaturate.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

StudyMatSaturate::StudyMatSaturate()
{
}


StudyMatSaturate::~StudyMatSaturate()
{
}

int StudyMatSaturate::Start()
{
	Matx<uchar, 2, 2> m1;
	Matx<ushort, 2, 2> m2;

	m1(0, 0) = -50;
	m1(0, 1) = 300;
	m1(1, 0) = saturate_cast<uchar>(-50);
	m1(1, 1) = saturate_cast<uchar>(300);

	m2(0, 0) = -50;
	m2(0, 1) = 800000;
	m2(1, 0) = saturate_cast<ushort>(-50);
	m2(1, 1) = saturate_cast<ushort>(800000);

	cout << "[m1] = " << endl << m1 << endl;
	cout << "[m2] = " << endl << m2 << endl;

	return 0;
}

