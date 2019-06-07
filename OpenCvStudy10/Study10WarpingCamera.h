#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study10WarpingCamera
{
public:
	Study10WarpingCamera();
	~Study10WarpingCamera();
	int Start();

private:
	vector<Point2f> findImageCorners(Mat image, Size boardSize);
	vector<Point3f> calcObjectCorners(Size boradSize, float squareSize);
};

