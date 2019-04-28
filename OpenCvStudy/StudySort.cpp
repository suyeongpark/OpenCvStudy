#include "pch.h"
#include "StudySort.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudySort::StudySort()
{
}


StudySort::~StudySort()
{
}

int StudySort::Start()
{
	Mat_<uchar> m1(3, 5);
	m1 << 11, 2, 3, 4, 10,
		6, 10, 15, 9, 7,
		7, 12, 8, 14, 1;

	Mat m_sort1, m_sort2, m_sort3, m_sort_idx1, m_sort_idx2;
	cv::sort(m1, m_sort1, SORT_EVERY_ROW);
	cv::sort(m1, m_sort2, SORT_EVERY_ROW + SORT_DESCENDING);
	cv::sort(m1, m_sort3, SORT_EVERY_COLUMN);

	cout << "[m1] = " << endl << m1 << endl;
	cout << "[m_sort1] = " << endl << m_sort1 << endl;
	cout << "[m_sort2] = " << endl << m_sort2 << endl;
	cout << "[m_sort3] = " << endl << m_sort3 << endl;

	return 0;
}
