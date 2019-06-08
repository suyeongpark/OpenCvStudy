#include "pch.h"
#include "Study12CalcCoins.h"


Study12CalcCoins::Study12CalcCoins()
{
}


Study12CalcCoins::~Study12CalcCoins()
{
}

int Study12CalcCoins::Start()
{
	int coin_no, hue_bin = 32;
	cout << "동전 영상번호: ";
	cin >> coin_no;
	string fname = format("D:/Dev/Study/Open CV 영상처리_학습자용/교재예제/12장_예제/12장_1절/image/%2d.png", coin_no);
	Mat image = imread(fname, 1);
	CV_Assert(image.data);

	Mat th_img = preprocessing(image);
	vector<RotatedRect> circles = find_coins(th_img);
	vector<Mat> coins_img = make_coinImg(image, circles);
	vector<Mat> coins_hist = calc_coin_histo(coins_img, hue_bin);

	int Ncoins[4] = { 0 };
	vector<int> groups = grouping(coins_hist);
	classify_coins(circles, groups, Ncoins);
	int coin_count = calc_coins(Ncoins);

	string str = format("total coin: %d won", coin_count);
	cout << str << endl;
	putText(image, str, Point(10, 50), 1, 2, Scalar(0, 200, 0), 2);
	draw_circle(image, circles, groups);
	imshow("결과 영상", image);
	waitKey();

	return 0;
}

Mat Study12CalcCoins::preprocessing(Mat img)
{
	Mat gray, th_img;

	cvtColor(img, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(7, 7), 2, 2);

	threshold(gray, th_img, 130, 255, THRESH_BINARY | THRESH_OTSU);
	morphologyEx(th_img, th_img, MORPH_OPEN, Mat(), Point(-1, -1), 1);

	return th_img;
}

vector<RotatedRect> Study12CalcCoins::find_coins(Mat img)
{
	vector<vector<Point>> contours;
	findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<RotatedRect> circles;

	for (int i = 0; i < (int)contours.size(); i++)
	{
		RotatedRect mr = minAreaRect(contours[i]);
		mr.angle = (mr.size.width + mr.size.height) / 4.0f;

		if (mr.angle > 18)
		{
			circles.push_back(mr);
		}
	}

	return circles;
}

vector<Mat> Study12CalcCoins::make_coinImg(const Mat src, vector<RotatedRect> circles)
{
	vector<Mat> coins;

	for (int i = 0; i < (int)circles.size(); i++)
	{
		int radius = (int)circles[i].angle;
		Size2f size = circles[i].size * 1.5f;
		Point2f center = size * 0.5f;

		Mat coin, mask(size, CV_8UC3, Scalar(0, 0, 0));
		circle(mask, center, radius, Scalar(255, 255, 255), FILLED);

		getRectSubPix(src, size, circles[i].center, coin);
		bitwise_and(coin, mask, coin);
		coins.push_back(coin);
	}

	return coins;
}

void Study12CalcCoins::calc_histo(const Mat& image, Mat& hist, Vec3i bins, Vec3f range, int _dims)
{
	int dims = (_dims <= 0) ? image.channels() : _dims;			// 히스토그램 차원수
	int		channels[] = { 0, 1, 2 };
	int		histSize[] = { bins[0], bins[1], bins[2] };

	float  range1[] = { 0, range[0] };
	float  range2[] = { 0, range[1] };
	float  range3[] = { 0, range[2] };
	const float* ranges[] = { range1, range2, range3 };

	calcHist(&image, 1, channels, Mat(), hist, dims, histSize, ranges);
}

vector<Mat> Study12CalcCoins::calc_coin_histo(vector<Mat> coins, int hue_bin)
{
	vector<Mat> histo;

	for (int i = 0; i < (int)coins.size(); i++)
	{
		Mat hsv, hist, hist_img;
		cvtColor(coins[i], hsv, COLOR_BGR2HSV);
		calc_histo(hsv, hist, Vec3i(hue_bin, 0, 0), Vec3f(180, 0, 0), 1);

		hist.at<float>(0) = 0;
		hist.at<float>(1) = 0;
		normalize(hist, hist, 0, 1, NORM_MINMAX);
		histo.push_back(hist);
	}

	return histo;
}

void Study12CalcCoins::classify_coins(vector<RotatedRect> circles, vector<int>& groups, int Ncoins[4])
{
	for (int i = 0; i < (int)circles.size(); i++)
	{
		int coin = 0;
		int radius = cvRound(circles[i].angle);

		if (groups[i] == 0)
		{
			if (radius > 48)
			{
				coin = 3;
			}
			else if (radius > 46)
			{
				coin = 2;
			}
			else if (radius > 25)
			{
				coin = 0;
			}
		}
		else if (groups[i] == 1)
		{
			if (radius > 48)
			{
				coin = 3;
			}
			else if (radius > 43)
			{
				coin = 2;
			}
			else if (radius > 25)
			{
				coin = 1;
			}
		}

		Ncoins[coin]++;
	}
}

int Study12CalcCoins::calc_coins(int Ncoins[4])
{
	int coin_value[] = { 10, 50,100,500 };
	int count = 0;

	for (int i = 0; i < 4; i++)
	{
		count += coin_value[i] * Ncoins[i];
		cout << format("%3d원: %3d 개", coin_value[i], Ncoins[i]) << endl;
	}

	return count;
}

void Study12CalcCoins::draw_circle(Mat & image, vector<RotatedRect> circles, vector<int> groups)
{
	Scalar color[]{
		Scalar(0, 0, 255),
		Scalar(255, 0, 0),
		Scalar(200, 50, 0),
		Scalar(200, 0, 200),
	};

	for (int i = 0; i < (int)circles.size(); i++)
	{
		int radius = cvRound(circles[i].angle);
		Point center = (Point)circles[i].center;
		circle(image, center, radius, color[groups[i]], 2);

		putText(image, to_string(i), center + Point(-10, 0), 1, 1, color[2], 2);
		putText(image, to_string(radius), center + Point(-10, 20), 1, 1, color[3], 2);
	}
}

vector<int> Study12CalcCoins::grouping(vector<Mat> hists)
{
	Matx<float, 32, 1> w[2], s[2];
	w[0] << 0, 0, 2, 2, 3, 5, 5, 4, 4, 3, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 3, 3, 2;
	w[1] << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0;

	vector<int> groups;
	for (int i = 0; i < (int)hists.size(); i++)
	{
		multiply(w[0], hists[i], s[0]);				// 히스토그램 유사도
		multiply(w[1], hists[i], s[1]);

		int group = (sum(s[0])[0] > sum(s[1])[0]) ? 0 : 1;
		groups.push_back(group);
	}
	return groups;
}
