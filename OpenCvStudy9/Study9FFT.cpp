#include "pch.h"
#include "Study9FFT.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Study9FFT::Study9FFT()
{
}


Study9FFT::~Study9FFT()
{
}

int Study9FFT::Start()
{
	string path = "D:\\Dev\\Study\\Open CV ����ó��_�н��ڿ�\\���翹��\\09��_����\\09��_2~4��\\image\\";
	Mat image = imread(path + "fft_test.jpg", 0);
	CV_Assert(image.data);

	Mat pad_img, complex_img, idft_img, img_tmp[2];
	Mat dft_coef1, dft_img1, shuffling_img1;
	Mat dft_coef2, dft_img2, shuffling_img2;

	pad_img = zeropadding(image);
	Mat tmp[] = { pad_img, Mat::zeros(pad_img.size(), pad_img.type()) };
	merge(tmp, 2, complex_img);

	FFT_2D(complex_img, dft_coef1, 1);
	log_mag(dft_coef1, dft_img1);
	shuffling(dft_img1, shuffling_img1);

	dft(complex_img, dft_coef2, 0);
	log_mag(dft_coef2, dft_img2);
	shuffling(dft_img2, shuffling_img2);

	dft(dft_coef2, idft_img, DFT_INVERSE + DFT_SCALE);
	split(idft_img, img_tmp);
	img_tmp[0].convertTo(img_tmp[0], CV_8U);


	imshow("image", image);
	imshow("shuffling_img1", shuffling_img1);
	imshow("shuffling_img2", shuffling_img2);
	imshow("idft_img", img_tmp[0]);
	waitKey();

	return 0;
}

void Study9FFT::log_mag(Mat complex_mat, Mat & dst)
{
	Mat planes[2];
	split(complex_mat, planes);
	magnitude(planes[0], planes[1], dst);
	log(dst + 1, dst);
	normalize(dst, dst, 0, 255, NORM_MINMAX);
	dst.convertTo(dst, CV_8U);
}

void Study9FFT::shuffling(Mat mag_img, Mat & dst)
{
	int cx = mag_img.cols / 2;
	int cy = mag_img.rows / 2;

	Rect q1(cx, 0, cx, cy);
	Rect q2(0, 0, cx, cy);
	Rect q3(0, cy, cx, cy);
	Rect q4(cx, cy, cx, cy);

	dst = Mat(mag_img.size(), mag_img.type());
	mag_img(q1).copyTo(dst(q3));
	mag_img(q3).copyTo(dst(q1));
	mag_img(q2).copyTo(dst(q4));
	mag_img(q4).copyTo(dst(q2));
}

Mat Study9FFT::scramble(Mat signal)
{
	Mat dst = signal.clone();

	for (int i = 0, j = 0; i < dst.cols - 1; i++)
	{
		if (i > j)
		{
			swap(dst.at<Vec2f>(i), dst.at<Vec2f>(j));
		}

		int m = dst.cols >> 1;

		while ((j >= m) && (m >= 2))
		{
			j -= m;
			m >>= 1;
		}

		j += m;
	}

	return dst;
}

Mat Study9FFT::zeropadding(Mat img)
{
	int m = 1 << (int)ceil(log2(img.rows));
	int n = 1 << (int)ceil(log2(img.cols));
	Mat dst(m, n, img.type(), Scalar(0));

	Rect rect(Point(0, 0), img.size());
	img.copyTo(dst(rect));
	dst.convertTo(dst, CV_32F);

	return dst;
}

void Study9FFT::butterfly(Mat & dst, int dir)
{
	int length = dst.cols;
	int pair = 1;

	for (int k = 0; k < ceil(log2(length)); k++)
	{
		int half_pair = pair;
		pair <<= 1;
		float theta = dir * (-2.0 * CV_PI / pair);
		float wpr = -2.0 * sin(0.5 * theta) * sin(0.5 * theta);
		float wpi = sin(theta);
		float wre = 1.0;
		float wim = 0.0;

		for (int m = 0; m < half_pair; m++)
		{
			for (int even = m; even < length; even += pair)
			{
				int odd = even + half_pair;
				Vec2f G_even = dst.at<Vec2f>(even);
				Vec2f G_odd = dst.at<Vec2f>(odd);

				Vec2f G_odd_W(0, 0);
				G_odd_W[0] = G_odd[0] * wre - G_odd[1] * wim;
				G_odd_W[1] = G_odd[1] * wre + G_odd[0] * wim;

				dst.at<Vec2f>(even) = G_even + G_odd_W;
				dst.at<Vec2f>(odd) = G_even - G_odd_W;
			}

			float tmp = wre;
			wre += tmp * wpr - wim * wpi;
			wim += wim * wpr + tmp * wpi;
		}
	}

	if (dir == -1)
	{
		dst /= dst.cols;
	}
}

void Study9FFT::FFT_2D(Mat complex_img, Mat & dst, int dir)
{
	dst = Mat(complex_img.size(), complex_img.type());

	for (int i = 0; i < complex_img.rows; i++)
	{
		Mat scr_sn = scramble(complex_img.row(i));
		butterfly(scr_sn, dir);
		scr_sn.copyTo(dst.row(i));
	}

	transpose(dst, dst);

	for (int i = 0; i < dst.rows; i++)
	{
		Mat scr_sn = scramble(dst.row(i));
		butterfly(scr_sn, dir);
		scr_sn.copyTo(dst.row(i));
	}

	transpose(dst, dst);
}
