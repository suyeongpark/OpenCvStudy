#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study10kNN_Test
{
public:
	Study10kNN_Test();
	~Study10kNN_Test();
	int Start();

private:
	void make_trainData(Mat trainData, Mat group[2], Mat& classLable);
	void draw_points(Mat& image, Mat group[2]);
	void kNN_test(Ptr<ml::KNearest> knn, int K, Mat& image);
};

