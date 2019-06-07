// OpenCvStudy10.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <opencv2/highgui.hpp>
#include "Study10WarpingCamera.h"

int main()
{
	Study10WarpingCamera study;
	study.Start();
}

//#include "pch.h"
//#include <iostream>
//#include <opencv2/highgui.hpp>
//#include <opencv2/opencv.hpp>
//#include "hough.hpp"
//using namespace cv;
//using namespace std;
//
//
//void detect_maxObject(Mat img, Rect & rect)
//{
//	vector<vector<Point>> contours;
//	findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//	int max_area = 0;
//
//	for (int i = 0; i < (int)contours.size(); i++)
//	{
//		Rect r = boundingRect(contours[i]);
//
//		if (max_area < r.area())
//		{
//			max_area = r.area();
//			rect = r;
//		}
//	}
//
//	rect = rect - Point(10, 10) + Size(20, 20);
//}
//
//int main()
//{
//	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\10장_예제\\image\\";
//	Mat image = imread(path + "5.tif", 1);
//	CV_Assert(image.data);
//
//	Rect rect;
//	Mat gray, canny, morph, th_gray, canny_line, dst;
//	double rho = 1, theta = CV_PI / 180;
//	vector<Vec2f> lines;
//
//	cvtColor(image, gray, COLOR_BGR2GRAY);
//	threshold(gray, th_gray, 240, 255, THRESH_BINARY);
//	erode(th_gray, morph, Mat(), Point(-1, -1), 2);
//
//	detect_maxObject(morph, rect);
//
//	Canny(th_gray(rect), canny, 40, 100);
//	houghLines(canny, lines, rho, theta, 50);
//	draw_houghLines(canny, canny_line, lines, 1);
//
//	double angle = (CV_PI - lines[0][1]) * 180 / CV_PI;
//	Point center = image.size() / 2;
//	Mat rot_map = getRotationMatrix2D(center, -angle, 1);
//
//	warpAffine(image, dst, rot_map, image.size(), INTER_LINEAR);
//
//	imshow("image", image);
//	imshow("canny_line", canny_line);
//	imshow("dst", dst);
//	waitKey();
//}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
