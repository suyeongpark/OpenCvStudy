#include "pch.h"
#include "StudyKeyEvent.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyKeyEvent::StudyKeyEvent()
{
}


StudyKeyEvent::~StudyKeyEvent()
{
}

int StudyKeyEvent::Start()
{
	Mat image(200, 300, CV_8U, Scalar(255));
	string title = "Ű���� �̺�Ʈ";
	namedWindow(title, WINDOW_AUTOSIZE);
	imshow(title, image);

	while (1)
	{
		int key = waitKey(100);
		if (key == 27) break;

		switch (key)
		{
		case 'a': cout << "aŰ �Է�" << endl; break;
		case 'b': cout << "bŰ �Է�" << endl; break;
		case 0x41: cout << "AŰ �Է�" << endl; break;
		case 66: cout << "BŰ �Է�" << endl; break;

		case 0x250000: cout << "���� ȭ��ǥ Ű �Է�" << endl; break;
		case 0x260000: cout << "���� ȭ��ǥ Ű �Է�" << endl; break;
		case 0x270000: cout << "������ ȭ��ǥ Ű �Է�" << endl; break;
		case 0x280000: cout << "�Ʒ��� ȭ��ǥ Ű �Է�" << endl; break;

		default:
			break;
		}
	}

	waitKey();

	return 0;
}
