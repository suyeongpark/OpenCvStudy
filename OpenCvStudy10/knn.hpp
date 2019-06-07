#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
//
//void StudyFindHistoPos(Mat img, int& start, int& end, int direct)
//{
//	reduce(img, img, direct, REDUCE_AVG);
//
//	int minFound = 0;
//
//	for (int i = 0; i < (int)img.total(); i++)
//	{
//		if (img.at<uchar>(i) < 250)
//		{
//			end = i;
//
//			if (!minFound)
//			{
//				start = i;
//				minFound = 1;
//			}
//		}
//	}
//}
//
//Mat StudyFindNumber(Mat part)
//{
//	Point start, end;
//	StudyFindHistoPos(part, start.x, end.x, 0);
//	StudyFindHistoPos(part, start.y, end.y, 1);
//
//	return part(Rect(start, end));
//}
//
//Mat StudyPlaceMiddle(Mat number, Size new_size)
//{
//	int big = max(number.cols, number.rows);
//	Mat square(big, big, number.type(), Scalar(255));
//
//	Point start = (square.size() - number.size()) / 2;
//	Rect middle(start, number.size());
//	number.copyTo(square(middle));
//
//	resize(square, square, new_size);
//	square.convertTo(square, CV_32F);
//	return square.reshape(0, 1);
//}