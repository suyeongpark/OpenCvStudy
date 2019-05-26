#include "pch.h"
#include "Study8Rotation2.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Mat image;

void onMouse(int event, int x, int y, int flags, void*);

Study8Rotation2::Study8Rotation2()
{
}


Study8Rotation2::~Study8Rotation2()
{
}

int Study8Rotation2::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\08장_예제\\08장_5~7절\\image\\";
	Mat image = imread(path + "rotate_test.jpg", 0);
	CV_Assert(image.data);

	imshow("image", image);
	setMouseCallback("image", onMouse, 0);
	waitKey();
	return 0;
}

uchar Study8Rotation2::bilinear_value(Mat img, double x, double y)
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

void Study8Rotation2::rotation(Mat img, Mat & dst, double dgree, Point pt)
{
	double radian = dgree / 180 * CV_PI;
	double sin_value = sin(radian);
	double cos_value = cos(radian);

	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			int jj = j - pt.x;
			int ii = i - pt.y;
			double x = jj * cos_value + ii * sin_value + pt.x;
			double y = -jj * sin_value + ii * cos_value + pt.y;

			if (rect.contains(Point2d(x, y)))
				dst.at<uchar>(i, j) = bilinear_value(img, x, y);
		}
	}
}

float Study8Rotation2::calc_angle(Point pt[3])
{
	Point2f d1 = pt[1] - pt[0];
	Point2f d2 = pt[2] - pt[0];
	float angle1 = fastAtan2(d1.y, d1.x);
	float angle2 = fastAtan2(d2.y, d2.x);

	return angle2 - angle1;
}

void onMouse(int event, int x, int y, int flags, void*)
{
	Point curr_pt(x, y);
	static Point pt[3] = {};
	static Mat tmp;

	if (flags == (EVENT_FLAG_LBUTTON | EVENT_FLAG_CTRLKEY))
	{
		pt[0] = curr_pt;
		tmp = image.clone();
		circle(tmp, pt[0], 2, Scalar(255), 2);
		imshow("image", tmp);
		cout << "회전 중심 : " << pt[0] << endl;
	}
	else if (event == EVENT_LBUTTONDOWN && pt[0].x > 0)
	{
		pt[1] = curr_pt;
		circle(tmp, pt[1], 2, Scalar(255), 2);
		imshow("image", tmp);
	}
	else if (event == EVENT_LBUTTONUP && pt[1].x > 0)
	{
		pt[2] = curr_pt;
		circle(tmp, pt[2], 2, Scalar(255), 2);
		imshow("image", tmp);
	}
/*
	if (pt[2].x > 0)
	{
		float angle = calc_angle(pt);
		cout << "회전각: " << angle << endl;

		Mat dst;
		rotation(image, dst, angle, pt[0]);
		imshow("image", dst);
		pt[0] = pt[1] = pt[2] = Point(0, 0);
	}*/
}
