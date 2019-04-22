#include "pch.h"
#include "StudyReadFileStorage.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyReadFileStorage::StudyReadFileStorage()
{
}


StudyReadFileStorage::~StudyReadFileStorage()
{
}

int StudyReadFileStorage::Start()
{
	FileStorage fs("C:\\Users\\suyeo\\Downloads\\text.xml", FileStorage::READ);
	CV_Assert(fs.isOpened());

	string name, university, picture;
	int age;
	fs["university"] >> university;
	fs["name"] >> name;
	fs["age"] >> age;

	cout << "university" << university << endl;
	cout << "name" << name << endl;
	cout << "age" << age << endl;

	FileNode node_pic = fs["picture"];
	FileNode node_hd = fs["hardware"];

	try
	{
		if (node_pic.type() != FileNode::SEQ)
			CV_Error(Error::StsError, "시퀀스 노드가 아닙니다.");

		if (!node_hd.isMap())
			CV_Error(Error::StsError, "매핑 노드가 아닙니다.");
	}
	catch (Exception &e)
	{
		exit(1);
	}

	cout << "[picture] ";
	cout << (string)node_pic[0] << ", ";
	cout << (string)node_pic[1] << ", ";
	cout << (string)node_pic[2] << endl << endl;

	cout << "[hardware] ";
	cout << " cpu " << (int)node_hd["cpu"] << endl;
	cout << " mainboard " << (int)node_hd["mainboard"] << endl;
	cout << " ram " << (int)node_hd["ram"] << endl;

	Point pt;
	Rect rect;
	Mat mat;
	vector<float> vec;
	fs["vector"] >> vec;
	fs["Point"] >> pt;
	fs["Rect"] >> rect;
	fs["Mat"] >> mat;

	cout << "[vec] = " << ((Mat)vec).t() << endl;
	cout << "[pt] = " << pt << endl;
	cout << "[rect] = " << rect << endl;
	cout << "[mat] = " << mat << endl;

	fs.release();

	return 0;
}
