#include "pch.h"
#include "Study8AffineTransform.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study8AffineTransform::Study8AffineTransform()
{
}


Study8AffineTransform::~Study8AffineTransform()
{
}

int Study8AffineTransform::Start()
{
	string path = "D:\\Dev\\Study\\Open CV ����ó��_�н��ڿ�\\���翹��\\08��_����\\08��_5~7��\\image\\";
	Mat image = imread(path + "affine_test.jpg", 0);
	CV_Assert(image.data);

	Point2f pt1[3] = { Point2f(10, 200), Point2f(200, 150), Point2f(300, 300), };
	Point2f pt2[3] = { Point2f(10, 10), Point2f(250, 10), Point2f(300, 300), };
	Point center(200, 100);
	double angle = 30.0;
	double scale = 1;

	Mat aff_map = getAffineTransform(pt1, pt2);
	Mat rot_map = getRotationMatrix2D(center, angle, scale);

	Mat dst1, dst2, dst3, dst4;
	affine_tranform(image, dst1, aff_map, image.size());
	affine_tranform(image, dst2, rot_map, image.size());

	warpAffine(image, dst3, aff_map, image.size(), INTER_LINEAR);
	warpAffine(image, dst4, rot_map, image.size(), INTER_LINEAR);

	cvtColor(image, image, COLOR_GRAY2BGR);
	cvtColor(dst1, dst1, COLOR_GRAY2BGR);

	for (int i = 0; i < 3; i++)
	{
		circle(image, pt1[i], 3, Scalar(0, 0, 255), 2);
		circle(dst1, pt2[i], 3, Scalar(0, 0, 255), 2);
	}

	imshow("image", image);
	imshow("dst1-������", dst1); 
	imshow("dst2-������ ȸ��", dst2);
	imshow("dst3-������_OpenCV", dst3); 
	imshow("dst4-������ -ȸ��_OpenCV", dst4);
	waitKey();

	return 0;
}

uchar Study8AffineTransform::bilinear_value(Mat img, double x, double y)
{
	if (x >= img.cols - 1)
		x--;

	if (y >= img.rows - 1)
		y--;

	Point pt((int)x, (int)y);
	int A = img.at<uchar>(pt);
	int B = img.at<uchar>(pt + Point(0, 1));
	int C = img.at<uchar>(pt + Point(1, 0));
	int D = img.at<uchar>(pt + Point(1, 1));

	double alpha = y - pt.y;
	double beta = x - pt.x;
	int M1 = A + (int)cvRound(alpha * (B - A));
	int M2 = C + (int)cvRound(alpha * (D - C));
	int P = M1 + (int)cvRound(beta * (M2 - M1));

	return saturate_cast<uchar>(P);
}

void Study8AffineTransform::affine_tranform(Mat img, Mat & dst, Mat map, Size size)
{
	dst = Mat(img.size(), img.type(), Scalar(0));
	Rect rect(Point(0, 0), img.size());

	Mat inv_map;
	invertAffineTransform(map, inv_map);

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			Point3d ji(j, i, 1);
			Mat xy = inv_map * (Mat)ji;
			Point2d pt = (Point2d)xy;

			if (rect.contains(pt))
				dst.at<uchar>(i, j) = bilinear_value(img, pt.x, pt.y);
		}
	}
}
