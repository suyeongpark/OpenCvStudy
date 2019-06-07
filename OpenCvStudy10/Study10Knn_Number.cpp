#include "pch.h"
#include "Study10Knn_Number.h"


Study10Knn_Number::Study10Knn_Number()
{
}


Study10Knn_Number::~Study10Knn_Number()
{
}

int Study10Knn_Number::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\10장_예제\\image\\";
	Mat train_image = imread(path + "train_numbers.png", 0);
	CV_Assert(train_image.data);
/*
	Size size(40, 40);
	int K = 15;
	int Nclass = 10;
	int Nsample = 20;

	threshold(train_image, train_image, 32, 255, THRESH_BINARY);

	Mat trainData, classLable;

	for (int i = 0, k = 0; i < Nclass; i++)
	{
		for (int j = 0; j < Nsample; j++, k++)
		{
			Point start(j * size.width, i * size.height);
			Rect roi(start, size);
			Mat part = train_image(roi);

			Mat num = StudyFindNumber(part);
			Mat data = StudyPlaceMiddle(num, size);
			trainData.push_back(data);
			classLable.push_back(i);
		}
	}

	Ptr<ml::KNearest> knn = ml::KNearest::create();
	knn->train(trainData, ml::ROW_SAMPLE, classLable);

	int no;
	cout << "영상번호를 입력하세요: ";
	cin >> no;

	string demo_file = format("D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\10장_예제\\image\\num\\%02d.png", no);
	Mat test_img = imread(demo_file, 0);
	CV_Assert(test_img.data);

	threshold(test_img, test_img, 128, 255, THRESH_BINARY);
	Mat num = StudyFindNumber(test_img);
	Mat data = StudyPlaceMiddle(num, size);

	Mat result;
	knn->findNearest(data, K, result);

	cout << "분류결과: " << result.at<float>(0) << endl;
	imshow("test_img", test_img);
	waitKey();*/

	return 0;
}
