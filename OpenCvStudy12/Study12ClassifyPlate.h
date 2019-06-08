#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study12ClassifyPlate
{
public:
	Study12ClassifyPlate();
	~Study12ClassifyPlate();
	int Start();

private:
	void collect_trainImage(Mat& trainingData, Mat& labels, int Nimages = 140);
	void write_traindata(string fn, Mat trainingData, Mat classes);
	void read_traindata(string fn, Mat& trainingData, Mat& labels);
	Ptr<ml::SVM> SVM_create(int type, int max_iter, double epsilon);
	Mat preprocessing(Mat image);
	bool vertify_plate(RotatedRect mr);
	void find_candidates(Mat img, vector<RotatedRect>& candidates);
	void draw_rotatedRect(Mat& img, RotatedRect mr, Scalar color, int thickness = 2);
	void refine_candidate(Mat image, RotatedRect& candi);
	void rotate_plate(Mat image, Mat& corp_img, RotatedRect candi);
	vector<Mat> make_candidate(Mat image, vector<RotatedRect>& candidates);
	int classify_plates(Ptr<ml::SVM> svm, vector<Mat> candi_img);
};

