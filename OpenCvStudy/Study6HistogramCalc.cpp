#include "pch.h"
#include "Study6HistogramCalc.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study6HistogramCalc::Study6HistogramCalc()
{
}


Study6HistogramCalc::~Study6HistogramCalc()
{
}

int Study6HistogramCalc::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\06장_예제\\06장_1절\\image\\";
	Mat image = imread(path + "pixel_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Mat hist;
	calc_histo(image, hist, 256);
	cout << hist.t() << endl;

	imshow("image", image);
	waitKey();
	return 0;
}

// header에서 선언했기 때문에 여기서 선택 매개변수를 쓸 필요는 없다.
//void Study6HistogramCalc::calc_histo(Mat image, Mat& hist, int bins, int range_max)
//{
//	hist = Mat(bins, 1, CV_32F, Scalar(0));
//	float gap = range_max / (float)bins;
//
//	for (int i = 0; i < image.rows; i++)
//	{
//		for (int j = 0; j < image.cols; j++)
//		{
//			int idx = int(image.at<uchar>(i, j) / gap);
//			hist.at<float>(idx)++;
//		}
//	}
//}


// header에서 선언했기 때문에 여기서 선택 매개변수를 쓸 필요는 없다.
void Study6HistogramCalc::calc_histo(const Mat& image, Mat& hist, int bins, int range_max)
{
	int histSize[] = { bins };
	float range[] = { 0, (float)range_max };
	int channels[] = { 0, };
	const float* ranges[] = { range };

	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}
