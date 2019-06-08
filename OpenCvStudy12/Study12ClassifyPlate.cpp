#include "pch.h"
#include "Study12ClassifyPlate.h"


Study12ClassifyPlate::Study12ClassifyPlate()
{
}


Study12ClassifyPlate::~Study12ClassifyPlate()
{
}

int Study12ClassifyPlate::Start()
{
	Ptr<ml::SVM> svm = ml::StatModel::load<ml::SVM>("../SVMtrain.xml");

	int car_no;	
	cout << "차량 영상 번호 (0-20) : ";
	cin >> car_no;

	string fn = format("D:/Dev/Study/Open CV 영상처리_학습자용/교재예제/12장_예제/12장_2절/image//test_car/%02d.jpg", car_no);
	Mat image = imread(fn, 1);
	CV_Assert(image.data);

	Mat morph = preprocessing(image);
	vector<RotatedRect> candidates;
	find_candidates(morph, candidates);
	vector<Mat> candidate_img = make_candidate(image, candidates);

	int plate_no = classify_plates(svm, candidate_img);

	if (plate_no >= 0)
		draw_rotatedRect(image, candidates[plate_no], Scalar(0, 255, 0), 2);

	imshow("번호판영상", candidate_img[plate_no]);
	imshow("image", image);
	waitKey();

	return 0;
}

void Study12ClassifyPlate::collect_trainImage(Mat & trainingData, Mat & labels, int Nimages)
{
	for (int i = 0; i < Nimages; i++)
	{
		string fname = format("D:/Dev/Study/Open CV 영상처리_학습자용/교재예제/12장_예제/12장_2절/image/train/%03d.png", i);
		Mat img = imread(fname, 0);
		CV_Assert(img.data);

		Mat tmp = img.reshape(1, 1);
		int label = (i < 70) ? 1 : 0;
		trainingData.push_back(tmp);
		labels.push_back(label);
	}

	trainingData.convertTo(trainingData, CV_32FC1);
}

void Study12ClassifyPlate::write_traindata(string fn, Mat trainingData, Mat classes)
{
	FileStorage fs(fn, FileStorage::WRITE);
	fs << "TrainingData" << trainingData;
	fs << "classes" << classes;
	fs.release();
}

void Study12ClassifyPlate::read_traindata(string fn, Mat& trainingData, Mat & labels)
{
	FileStorage fs(fn, FileStorage::READ);
	CV_Assert(fs.isOpened());

	fs["TrainingData"] >> trainingData;
	fs["classes"] >> labels;
	fs.release();

	trainingData.convertTo(trainingData, CV_32FC1);
}

Ptr<ml::SVM> Study12ClassifyPlate::SVM_create(int type, int max_iter, double epsilon)
{
	Ptr<ml::SVM> svm = ml::SVM::create();
	svm->setType(ml::SVM::C_SVC);
	svm->setKernel(ml::SVM::LINEAR);
	svm->setGamma(1);
	svm->setC(1);
	TermCriteria criteria(type, max_iter, epsilon);
	svm->setTermCriteria(criteria);
	return svm;
}

Mat Study12ClassifyPlate::preprocessing(Mat image)
{
	Mat gray, th_img, morph;
	Mat kernel(5, 15, CV_8UC1, Scalar(1));
	cvtColor(image, gray, COLOR_BGR2GRAY);
	blur(gray, gray, Size(5, 5));
	Sobel(gray, gray, CV_8U, 1, 0, 3);
	threshold(gray, th_img, 120, 255, THRESH_BINARY);
	morphologyEx(th_img, morph, MORPH_CLOSE, kernel, Point(-1, -1), 2);

	imshow("th_img", th_img);
	imshow("morph", morph);

	return morph;
}

bool Study12ClassifyPlate::vertify_plate(RotatedRect mr)
{
	float size = mr.size.area();
	float aspect = (float)mr.size.height / mr.size.width;

	if (aspect < 1)
	{
		aspect = 1 / aspect;
	}

	bool ch1 = size > 2000 && size < 30000;
	bool ch2 = aspect > 1.3 && aspect < 6.4;

	return ch1 && ch2;
}

void Study12ClassifyPlate::find_candidates(Mat img, vector<RotatedRect>& candidates)
{
	vector<vector<Point>> contours;
	findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < (int)contours.size(); i++)
	{
		RotatedRect rot_rect = minAreaRect(contours[i]);

		if (vertify_plate(rot_rect))
		{
			candidates.push_back(rot_rect);
		}
	}
}


void Study12ClassifyPlate::draw_rotatedRect(Mat & img, RotatedRect mr, Scalar color, int thickness)
{
	Point2f pts[4];
	mr.points(pts);

	for (int i = 0; i < 4; ++i)
	{
		line(img, pts[i], pts[(i + 1) % 4], color, thickness);
	}
}

void Study12ClassifyPlate::refine_candidate(Mat image, RotatedRect & candi)
{
	Mat fill(image.size() + Size(2, 2), CV_8UC1, Scalar(0));
	Scalar dif1(25, 25, 25), dif2(25, 25, 25);
	int flags = 4 + 0xff00;
	flags += FLOODFILL_FIXED_RANGE + FLOODFILL_MASK_ONLY;

	vector<Point2f> rand_pt(15);
	randn(rand_pt, 0, 7);
	Rect img_rect(Point(0, 0), image.size());

	for (int i = 0; i < rand_pt.size(); i++)
	{
		Point2f seed = candi.center + rand_pt[i];

		if (img_rect.contains(seed))
		{
			floodFill(image, fill, seed, Scalar(), &Rect(), dif1, dif2, flags);
		}
	}

	vector<Point> fill_pts;

	for (int i = 0; i < fill.rows; i++)
	{
		for (int j = 0; j < fill.cols; j++)
		{
			if (fill.at<uchar>(i, j) == 255)
			{
				fill_pts.push_back(Point(j, i));
			}
		}
	}

	candi = minAreaRect(fill_pts);
}

void Study12ClassifyPlate::rotate_plate(Mat image, Mat & corp_img, RotatedRect candi)
{
	float aspect = (float)candi.size.width / candi.size.height;
	float angle = candi.angle;

	if (aspect < 1)
	{
		swap(candi.size.width, candi.size.height);
		angle += 90;
	}

	Mat rotmat = getRotationMatrix2D(candi.center, angle, 1);
	warpAffine(image, corp_img, rotmat, image.size(), INTER_CUBIC);
	getRectSubPix(corp_img, candi.size, candi.center, corp_img);
}

vector<Mat> Study12ClassifyPlate::make_candidate(Mat image, vector<RotatedRect>& candidates)
{
	vector<Mat> candidates_img;

	for (int i = 0; i < (int)candidates.size(); i++)
	{
		refine_candidate(image, candidates[i]);

		if (vertify_plate(candidates[i]))
		{
			Mat corp_img;
			rotate_plate(image, corp_img, candidates[i]);

			cvtColor(corp_img, corp_img, COLOR_BGR2GRAY);
			resize(corp_img, corp_img, Size(144, 28), 0, 0, INTER_CUBIC);
			candidates_img.push_back(corp_img);
		}
		else
		{
			candidates.erase(candidates.begin() + i);
		}
	}

	return candidates_img;
}

int Study12ClassifyPlate::classify_plates(Ptr<ml::SVM> svm, vector<Mat> candi_img)
{
	for (int i = 0; i < (int)candi_img.size(); i++)
	{
		Mat onerow = candi_img[i].reshape(1, 1);
		onerow.convertTo(onerow, CV_32F);

		Mat results;
		svm->predict(onerow, results);

		if (results.at<float>(0) == 1)
		{
			return i;
		}
	}

	return -1;
}
