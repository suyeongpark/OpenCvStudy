#include "pch.h"
#include "StudyWriteFileStorage.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyWriteFileStorage::StudyWriteFileStorage()
{
}


StudyWriteFileStorage::~StudyWriteFileStorage()
{
}

int StudyWriteFileStorage::Start()
{
	FileStorage fs("C:\\Users\\suyeo\\Downloads\\text.xml", FileStorage::WRITE);
	fs << "name" << "¹Ú¼ö¿µ";
	fs << "age" << 38;
	fs << "university" << "none";
	fs << "picture" << "[" << "mine1.jpg" << "mine2.jpg" << "mine3.jpg" << "]";
	fs << "hardware" << "{";
	fs << "cpu" << 25;
	fs << "mainboard" << 10;
	fs << "ram" << 6 << "}";

	int data[] = {1, 2, 3, 4, 5, 6};
	vector<int> vec(data, data + sizeof(data) / sizeof(float));
	fs << "vector" << vec;
	Mat m(2, 3, CV_32S, data);
	fs << "mat" << m;

	Point2d pt(10.5, 200);
	Rect rect(pt, Size(100, 200));
	fs << "Point" << pt;
	fs << "Rect" << rect;

	fs.release();

	return 0;
}
