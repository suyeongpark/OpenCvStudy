#include "pch.h"
#include "StudyImageDataWrite.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyImageDataWrite::StudyImageDataWrite()
{
}


StudyImageDataWrite::~StudyImageDataWrite()
{
}

int StudyImageDataWrite::Start()
{
	FileStorage fs_r("C:\\Users\\suyeo\\Downloads\\text.xml", FileStorage::READ);
	CV_Assert(fs_r.isOpened());

	FileNode node_pic = fs_r["picture"];
	vector<Mat> images;

	for (int i = 0; i < node_pic.size(); i++)
	{
		Mat tmp = imread("D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\04장_예제\\04장_5~6절\\image\\" + (string)node_pic[i], IMREAD_UNCHANGED);
		CV_Assert(tmp.data);
		images.push_back(tmp);
		imshow(node_pic[i], images[i]);
	}

	FileStorage fs_w("C:\\Users\\suyeo\\Downloads\\result.xml", FileStorage::WRITE);
	CV_Assert(fs_w.isOpened());

	vector<double> mean, dev;

	for (int i = 0; i < images.size(); i++)
	{
		string pic_name = ((string)node_pic[i]).substr(0, 5);

		meanStdDev(images[i], mean, dev);
		fs_w << pic_name + "_mean" << "[";

		for (int j = 0; j < (int)mean.size(); j++)
		{
			fs_w << mean[j];
		}

		fs_w << "]";
		fs_w << pic_name + "_dev" << dev;
	}

	waitKey();
	fs_r.release();
	fs_w.release();


	return 0;
}
