#include "pch.h"
#include "StudyPixelValue.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyPixelValue::StudyPixelValue()
{
}


StudyPixelValue::~StudyPixelValue()
{
}

int StudyPixelValue::Start()
{
	string path = "D:\\Dev\\Study\\Open CV ����ó��_�н��ڿ�\\���翹��\\06��_����\\06��_1��\\image\\";
	Mat image = imread(path + "pixel_test.jpg", IMREAD_GRAYSCALE);

	if (image.empty())
	{
		cout << "������ ���� �� �߽��ϴ�." << endl;
		exit(1);
	}

	Rect roi(200, 300, 20, 20);
	Mat roi_img = image(roi);

	cout << "[roi_img] = " << endl;

	for (int i = 0; i < roi_img.rows; i++)
	{
		for (int j = 0; j < roi_img.cols; j++)
		{
			cout.width(5);
			cout << (int)roi_img.at<uchar>(i, j);
		}
		cout << endl;
	}

	rectangle(image, roi, Scalar(255), 1);
	imshow("image", image);
	waitKey();

	return 0;
}
