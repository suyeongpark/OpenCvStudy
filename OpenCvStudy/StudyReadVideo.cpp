#include "pch.h"
#include "StudyReadVideo.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyReadVideo::StudyReadVideo()
{
}


StudyReadVideo::~StudyReadVideo()
{
}

int StudyReadVideo::Start()
{
	VideoCapture capture;
	capture.open("D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\04장_예제\\04장_5~6절\\image\\move_file.avi");
	CV_Assert(capture.isOpened());

	double frame_rate = capture.get(CAP_PROP_FPS);
	int delay = 1000 / frame_rate;
	int frame_count = 0;
	Mat frame;

	while (capture.read(frame))
	{
		if (waitKey(delay) >= 0)
			break;

		if (frame_count < 100);
		else if (frame_count < 200) frame -= Scalar(0, 0, 100);
		else if (frame_count < 300) frame += Scalar(1000, 0, 0);
		else if (frame_count < 400) frame = frame * 1.5;
		else if (frame_count < 500) frame = frame * 0.5;

		put_string(frame, "frame_count", Point(20, 50), frame_count);
		imshow("동영상 파일읽기", frame);
	}

	return 0;
}


void StudyReadVideo::put_string(Mat& frame, string text, Point pt, int value)
{
	text += to_string(value);
	Point shade = pt + Point(2, 2);
	int font = FONT_HERSHEY_SIMPLEX;
	putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);
	putText(frame, text, pt, font, 0.7, Scalar(120, 200, 90), 2);
}
