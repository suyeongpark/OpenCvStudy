#include "pch.h"
#include "Study11ImageSearch.h"


Study11ImageSearch::Study11ImageSearch()
{
}


Study11ImageSearch::~Study11ImageSearch()
{
}

int Study11ImageSearch::Start()
{
	Vec3i divs(30, 42, 0);
	Vec3f ranges(180, 256, 0);
	vector<Mat> DB_hists = load_hist(divs, ranges, 100);
	Mat query = query_img();

	Mat hsv, query_hist;
	cvtColor(query, hsv, COLOR_BGR2HSV);
	calc_Histo(hsv, query_hist, divs, ranges, 2);
	Mat hist_img = draw_histo(query_hist);

	Mat DB_similaritys = calc_similarity(query_hist, DB_hists);

	double sinc;
	cout << " 기준 유사도 입력: ";
	cin >> sinc;
	select_view(sinc, DB_similaritys);

	imshow("image", query);
	imshow("hist_img", hist_img);
	waitKey();

	return 0;
}

void Study11ImageSearch::calc_Histo(const Mat & img, Mat & hist, Vec3i bins, Vec3f range, int _dims)
{
	int dims = (_dims <= 0) ? img.channels() : _dims;
	int channels[] = { 0, 1, 2 };
	int histSize[] = { bins[0], bins[1], bins[2] };

	float range1[] = { 0, range[0] };
	float range2[] = { 0, range[1] };
	float range3[] = { 0, range[2] };
	const float* ranges[] = { range1, range2, range3 };

	calcHist(&img, 1, channels, Mat(), hist, dims, histSize, ranges);
	normalize(hist, hist, 0, 1, NORM_MINMAX);
}

Mat Study11ImageSearch::draw_histo(Mat hist)
{
	if (hist.dims != 2)
	{
		cout << "히스토그램이 2차원 데이터가 아닙니다" << endl;
		exit(1);
	}

	float ratio_value = 512.f;
	float ratio_hue = 180.f / hist.rows;
	float ratio_sat = 256.f / hist.cols;

	Mat graph(hist.size(), CV_32FC3);

	for (int i = 0; i < hist.rows; i++)
	{
		for (int j = 0; j < hist.cols; j++)
		{
			float value = hist.at<float>(i, j) * ratio_value;
			float hue = i * ratio_hue;
			float sat = j * ratio_sat;
			graph.at<Vec3f>(i, j) = Vec3f(hue, sat, value);
		}
	}

	graph.convertTo(graph, CV_8U);
	cvtColor(graph, graph, COLOR_HSV2BGR);
	resize(graph, graph, Size(0, 0), 10, 10, INTER_NEAREST);

	return graph;
}

vector<Mat> Study11ImageSearch::load_hist(Vec3i bins, Vec3f ranges, int nImages)
{
	vector<Mat> DB_hists;

	for (int i = 0; i < nImages; i++)
	{		
		string fname = format("D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\11장_예제\\11장_2절\\image\\DB\\img_%02d.jpg", i);
		Mat hsv, hist, img = imread(fname, IMREAD_COLOR);

		if (img.empty())
			continue;

		cvtColor(img, hsv, COLOR_BGR2HSV);
		calc_Histo(hsv, hist, bins, ranges, 2);
		DB_hists.push_back(hist);
	}

	cout << format("%d개 파일 로드 및 히스토그램 계산 완료", DB_hists.size());

	return DB_hists;
}

Mat Study11ImageSearch::query_img()
{
	do
	{
		int q_no = 74;
		cout << "질의영상 번호를 입력하세요: ";
		cin >> q_no;

		string fname = format("D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\11장_예제\\11장_2절\\image\\DB\\img_%02d.jpg", q_no);
		Mat query = imread(fname, IMREAD_COLOR);

		if (query.empty())
		{
			cout << "질의영상 번호가 잘못되었습니다" << endl;
		}
		else
		{
			return query;
		}

	} while (1);

	return Mat();
}

Mat Study11ImageSearch::calc_similarity(Mat query_hist, vector<Mat>& DB_hists)
{
	Mat DB_similaritys;

	for (int i = 0; i < (int)DB_hists.size(); i++)
	{
		double compare = compareHist(query_hist, DB_hists[i], HISTCMP_CORREL);
		DB_similaritys.push_back(compare);
	}

	return DB_similaritys;
}

void Study11ImageSearch::select_view(double sinc, Mat DB_similaritys)
{
	Mat m_idx, sorted_sim;
	int flag = SORT_EVERY_COLUMN + SORT_DESCENDING;
	cv::sort(DB_similaritys, sorted_sim, flag);
	sortIdx(DB_similaritys, m_idx, flag);

	for (int i = 0; i < (int)sorted_sim.total(); i++)
	{
		double sim = sorted_sim.at<double>(i);

		if (sim > sinc)
		{
			int idx = m_idx.at<int>(i);
			string fname = format("D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\11장_예제\\11장_2절\\image\\DB\\img_%02d.jpg", idx);
			Mat img = imread(fname, 1);

			string title = format("img_%03d - %5.2f", idx, sim);
			cout << title << endl;
			imshow(title, img);
		}
	}
}
