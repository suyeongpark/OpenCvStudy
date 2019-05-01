#include "pch.h"
#include "StudyImageSynthesis.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyImageSynthesis::StudyImageSynthesis()
{
}


StudyImageSynthesis::~StudyImageSynthesis()
{
}

int StudyImageSynthesis::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\06장_예제\\06장_1절\\image\\";
	Mat image1 = imread(path + "add1.jpg", IMREAD_GRAYSCALE);
	Mat image2 = imread(path + "add2.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!(image1.empty() || image2.empty()));

	double alpha = 0.6, beta = 0.7;
	Mat add_img1 = image1 + image2;
	Mat add_img2 = image1 * 0.5 + image2 * 0.5;
	Mat add_img3 = image1 * alpha + image2 * (1 - alpha);
	Mat add_img4;
	addWeighted(image1, alpha, image2, beta, 0, add_img4);

	imshow("image1", image1);
	imshow("image2", image2);
	imshow("add_image1", add_img1);
	imshow("add_image2", add_img2);
	imshow("add_image3", add_img3);
	imshow("add_image4", add_img4);
	waitKey();
	return 0;
}
