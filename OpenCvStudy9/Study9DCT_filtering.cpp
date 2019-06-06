#include "pch.h"
#include "Study9DCT_filtering.h"


Study9DCT_filtering::Study9DCT_filtering()
{
}


Study9DCT_filtering::~Study9DCT_filtering()
{
}

int Study9DCT_filtering::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\09장_예제\\09장_5절\\image\\";
	Mat image = imread(path + "dct_test2.jpg", 0);
	CV_Assert(image.data);

	Mat  dct_filter[5], dst[5];

	dct_filter[0] = getDCT_filter_dc(8, 8);
	dct_filter[1] = getDCT_filter_hori(8, 8);
	dct_filter[2] = getDCT_filter_verti(8, 8);
	dct_filter[3] = getDCT_filter_low(8, 8);
	dct_filter[4] = getDCT_filter_high(8, 8);

	for (int i = 0; i < 5; i++) 
	{
		DCT_filtering(image, dct_filter[i], dst[i], 8, 8);

		if (i == 4)
		{
			dst[i] *= 5;
		}

		imshow("dst[" + to_string(i) + "]", dst[i]);
	}

	imshow("image", image);
	waitKey();

	return 0;
}

Mat Study9DCT_filtering::DCT_block(Mat g)
{
	Mat dst(g.size(), g.type());
	int N = g.rows, M = g.cols;

	for (int k = 0; k < N; k++)
	{
		for (int l = 0; l < M; l++)
		{
			float sum = 0;

			for (int n = 0; n < N; n++)
			{
				for (int m = 0; m < M; m++)
				{
					float theta1 = (float)(2 * n + 1) * k * CV_PI / (2 * N);
					float theta2 = (float)(2 * m + 1) * l * CV_PI / (2 * M);
					sum += g.at<float>(n, m) * cos(theta1) * cos(theta2);
				}
			}

			float ck = (k) ? sqrt(2.0f / N) : sqrt(1.0f / N);
			float cl = (l) ? sqrt(2.0f / M) : sqrt(1.0f / M);
			dst.at<float>(k, l) = ck * cl * sum;
		}
	}

	return dst;
}

Mat Study9DCT_filtering::IDCT_block(Mat f)
{
	Mat dst(f.size(), f.type());
	int N = f.rows, M = f.cols;

	for (int n = 0; n < N; n++)
	{
		for (int m = 0; m < M; m++)
		{
			float sum = 0;

			for (int k = 0; k < N; k++)
			{
				for (int l = 0; l < M; l++)
				{
					float theta1 = (float)(2 * n + 1) * k * CV_PI / (2 * N);
					float theta2 = (float)(2 * m + 1) * l * CV_PI / (2 * M);

					float ck = (k) ? sqrt(2.0f / N) : sqrt(1.0f / N);
					float cl = (l) ? sqrt(2.0f / M) : sqrt(1.0f / M);
					sum += ck * cl * f.at<float>(k, l) * cos(theta1) * cos(theta2);
				}
			}

			dst.at<float>(n, m) = sum;
		}
	}

	return dst;
}

Mat Study9DCT_filtering::getDCT_filter_dc(int N, int M)
{
	Mat filter(N, M, CV_32F, Scalar(0));

	filter.at<float>(0, 0) = 1;

	return filter;
}

Mat Study9DCT_filtering::getDCT_filter_hori(int N, int M)
{
	Mat filter(N, M, CV_32F, Scalar(0));

	for (int i = 0; i < N; i++)
	{
		filter.at<float>(0, i) = 1;
	}

	return filter;
}

Mat Study9DCT_filtering::getDCT_filter_verti(int N, int M)
{
	Mat filter(N, M, CV_32F, Scalar(0));

	for (int i = 0; i < M; i++)
	{
		filter.at<float>(i, 0) = 1;
	}

	return filter;
}

Mat Study9DCT_filtering::getDCT_filter_low(int N, int M)
{
	Mat filter(N, M, CV_32F, Scalar(0));

	for (int i = 0; i < N / 2; i++)
	{
		for (int j = 0; j < M / 2; j++)
		{
			filter.at<float>(j, i) = 1;
		}
	}

	return filter;
}

Mat Study9DCT_filtering::getDCT_filter_high(int N, int M)
{
	Mat filter(N, M, CV_32F, Scalar(1));

	filter.at<float>(0, 0) = 0;  
	filter.at<float>(0, 1) = 0;
	filter.at<float>(0, 2) = 0;	
	filter.at<float>(1, 0) = 0;
	filter.at<float>(1, 1) = 0;	
	filter.at<float>(2, 1) = 0;

	return filter;
}

void Study9DCT_filtering::DCT_filtering(Mat img, Mat filter, Mat & dst, int N, int M)
{
	dst = Mat(img.size(), CV_32F);
	img.convertTo(img, CV_32F);

	for (int bi = 0; bi < img.rows; bi += N) 
	{
		for (int bj = 0; bj < img.cols; bj += M)
		{
			Rect rect(Point(bj, bi), Size(M, N));
			Mat new_block = DCT_block(img(rect));
			multiply(new_block, filter, new_block);

			IDCT_block(new_block).copyTo(dst(rect));
		}
	}

	dst.convertTo(dst, CV_8U);
}
