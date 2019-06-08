#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study11ImageSearch
{
public:
	Study11ImageSearch();
	~Study11ImageSearch();
	int Start();

private:
	void calc_Histo(const Mat& img, Mat& hist, Vec3i bins, Vec3f range, int _dims);
	Mat draw_histo(Mat hist);
	vector<Mat> load_hist(Vec3i bins, Vec3f ranges, int nImages);
	Mat query_img();
	Mat calc_similarity(Mat query_hist, vector<Mat>& DB_hists);
	void select_view(double sinc, Mat DB_similaritys);
};

