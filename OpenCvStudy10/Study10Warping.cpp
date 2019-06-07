#include "pch.h"
#include "Study10Warping.h"

Point2f pt1, pt2;
Mat image;

Study10Warping::Study10Warping()
{
}


Study10Warping::~Study10Warping()
{
}

int Study10Warping::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\10장_예제\\image\\";
	Mat train_image = imread(path + "warp_test.jpg", 0);
	CV_Assert(train_image.data);

	imshow("image", image);

	// 이런거는 아직 모르겠다.
	//setMouseCallback("image", std::bind(&Study10Warping::onMouse, this));
	waitKey();

	return 0;
}

void Study10Warping::morphing()
{
	Mat dst(image.size(), image.type(), Scalar(0));
	int width = image.cols;

	for (float y = 0; y < image.rows; y++)
	{
		for (float x = 0; x < image.cols; x++)
		{
			float ratio;

			if (x < pt1.x)
			{
				ratio = x / pt1.x;
			}
			else
			{
				ratio = (width - x) / (width - pt1.x);
			}

			float dx = ratio * (pt2.x - pt1.x);
			dst.at<uchar>(y, x + dx) = image.at<uchar>(y, x);
		}
	}
	dst.copyTo(image);
	imshow("image", image);
}


void Study10Warping::onMouse(int event, int x, int y, int flags, void* param)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		pt1 = Point2f(x, y);
	}
	else if (event == EVENT_LBUTTONUP)
	{
		pt2 = Point2f(x, y);
		morphing();
	}

}