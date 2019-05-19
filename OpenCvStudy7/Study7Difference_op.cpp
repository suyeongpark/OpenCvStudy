#include "pch.h"
#include "Study7Difference_op.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study7Difference_op::Study7Difference_op()
{
}


Study7Difference_op::~Study7Difference_op()
{
}

int Study7Difference_op::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\07장_예제\\07장_1절\\image\\";
	Mat image = imread(path + "edge_test.jpg", 0);
	CV_Assert(image.data);

	Mat edge;
	DifferOp(image, edge, 3);

	imshow("image", image);
	imshow("edge", edge);
	waitKey();

	return 0;
}

void Study7Difference_op::DifferOp(Mat img, Mat & dst, int mask_size)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	Point h_m(mask_size / 2, mask_size / 2);

	for (int i = h_m.y; i < img.rows - h_m.y; i++)
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			vector<uchar> mask;

			for (int u = 0; u < mask_size; u++)
			{
				for (int v = 0; v < mask_size; v++)
				{
					int y = i + u - h_m.y;
					int x = j + v - h_m.x;
					mask.push_back(img.at<uchar>(y, x));
				}
			}

			uchar max = 0;
			int maskSize = (int)mask.size();
			for (int k = 0; k < maskSize / 2; k++)
			{
				int start = mask[k];
				int end = mask[maskSize - k - 1];

				uchar difference = abs(start - end);

				if (difference > max)
				{
					max = difference;
				}
			}

			dst.at<uchar>(i, j) = max;
		}
	}
}
