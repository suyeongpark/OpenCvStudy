#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#pragma once
class Study11GenderClassifier
{
public:
	Study11GenderClassifier();
	~Study11GenderClassifier();
	int Start();

private:
	void load_cascade(CascadeClassifier& cascade, string fname);
	Mat preprocessing(Mat image);
	Point2d calc_center(Rect obj);
	Mat calc_rotMap(Point2d face_center, vector<Point2f> pt);
	Mat correct_image(Mat image, Mat rot_mat, vector<Point2f>& eyes_center);
	Rect detect_lip(Point2d face_center, Rect face);
	void detect_hair(Point2d face_center, Rect face, vector<Rect> &hair_rect);
	void calc_Histo(const Mat& img, Mat& hist, Vec3i bins, Vec3f range, Mat mask);
	void make_masks(vector<Rect> sub_obj, Size org_size, Mat mask[4]);
	void draw_ellipse(Mat& image, Rect2d obj, Scalar color, int thickness, double ratio);
	void calc_histos(Mat correct_img, vector<Rect> sub_obj, Mat hists[4], Mat masks[4]);
	void classify(Mat& image, Mat hists[4], int no);
	void display(Mat& image, Point2d face_center, vector<Point2f> eyes_center, vector<Rect> sub);
	bool key_check(int& no);
};

