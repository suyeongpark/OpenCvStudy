#include "pch.h"
#include "Study8Translation.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study8Translation::Study8Translation()
{
}


Study8Translation::~Study8Translation()
{
}

int Study8Translation::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\08장_예제\\08장_2~4절\\image\\";
	Mat image = imread(path + "translation_test.jpg", 0);
	CV_Assert(image.data);

	Mat dst1, dst2;
	translation(image, dst1, Point(30, 80));
	translation(image, dst2, Point(-80, -50));

	imshow("image", image);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();
	return 0;
}

void Study8Translation::translation(Mat img, Mat & dst, Point pt)
{
	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			Point dst_pt(j, i);
			Point img_pt = dst_pt - pt;

			if (rect.contains(img_pt))
				dst.at<uchar>(dst_pt) = img.at<uchar>(img_pt);
		}
	}
}
