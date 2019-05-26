#include "pch.h"
#include "Study8Scaling.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study8Scaling::Study8Scaling()
{
}


Study8Scaling::~Study8Scaling()
{
}

int Study8Scaling::Start()
{
	string path = "D:\\Dev\\Study\\Open CV ����ó��_�н��ڿ�\\���翹��\\08��_����\\08��_2~4��\\image\\";
	Mat image = imread(path + "scaling_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat dst1, dst2;
	scaling(image, dst1, Size(150, 200));
	scaling(image, dst2, Size(300, 400));

	imshow("image", image);
	imshow("dst1 - ���", dst1);
	imshow("dst2 - Ȯ��", dst2);
	resizeWindow("dst1-���", 200, 200);
	waitKey();

	return 0;
}

void Study8Scaling::scaling(Mat img, Mat & dst, Size size)
{
	dst = Mat(size, img.type(), Scalar(0));
	double ratioX = (double)size.width / img.cols;
	double ratioY = (double)size.height / img.rows;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			int x = (int)(j * ratioX);
			int y = (int)(i * ratioY);
			dst.at<uchar>(y, x) = img.at<uchar>(i, j);
		}
	}
}
