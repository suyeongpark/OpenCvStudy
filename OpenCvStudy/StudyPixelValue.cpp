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
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\06장_예제\\06장_1절\\image\\";
	Mat image = imread(path + "pixel_test.jpg", IMREAD_GRAYSCALE);

	if (image.empty())
	{
		cout << "영상을 읽지 못 했습니다." << endl;
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
