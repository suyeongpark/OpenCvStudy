#include "pch.h"
#include "Study7Homogenity_op.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study7Homogenity_op::Study7Homogenity_op()
{
}


Study7Homogenity_op::~Study7Homogenity_op()
{
}

int Study7Homogenity_op::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\07장_예제\\07장_1절\\image\\";
	Mat image = imread(path + "edge_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat edge;
	HomogenOp(image, edge, 3);

	imshow("image", image);
	imshow("edge-homogenOp", edge);
	waitKey();

	return 0;
}

void Study7Homogenity_op::HomogenOp(Mat img, Mat & dst, int mask_size)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	Point h_m(mask_size / 2, mask_size / 2);

	for (int i = h_m.y; i < img.rows - h_m.y; i++)
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			float max = 0;

			for (int u = 0; u < mask_size; u++)
			{
				for (int v = 0; v < mask_size; v++)
				{
					int y = i + u - h_m.y;
					int x = j + v - h_m.x;
					float difference = abs(img.at<uchar>(i, j) - img.at<uchar>(y, x));

					if (difference > max)
					{
						max = difference;
					}
				}
			}

			dst.at<uchar>(i, j) = max;
		}
	}
}
