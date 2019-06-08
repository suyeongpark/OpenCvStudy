#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study12CalcCoins
{
public:
	Study12CalcCoins();
	~Study12CalcCoins();
	int Start();

private:
	Mat preprocessing(Mat img);
	vector<RotatedRect> find_coins(Mat img);
	vector<Mat> make_coinImg(const Mat src, vector<RotatedRect> circles);
	vector<Mat> calc_coin_histo(vector<Mat> coins, int hue_bin);
	void classify_coins(vector<RotatedRect> circles, vector<int>& groups, int Ncoins[4]);
	int calc_coins(int Ncoins[4]);
	void draw_circle(Mat& image, vector<RotatedRect> circles, vector<int> groups);
	vector<int> grouping(vector<Mat> hists);
	void calc_histo(const Mat& image, Mat& hist, Vec3i bins, Vec3f range, int _dims);
};

