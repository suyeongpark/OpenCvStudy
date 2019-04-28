#include "pch.h"
#include "StudyMagnitude.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


StudyMagnitude::StudyMagnitude()
{
}


StudyMagnitude::~StudyMagnitude()
{
}

int StudyMagnitude::Start()
{
	float data1[] = { 1, 2, 3, 5, 10 };
	float data2[] = { 2, 5, 7, 2, 9, };
	vector<float> x_vec(data1, data1 + sizeof(data1) / sizeof(float));
	vector<float> y_vec(data2, data2 + sizeof(data2) / sizeof(float));

	vector<float> v_mag, v_ang;
	magnitude(x_vec, y_vec, v_mag);
	phase(x_vec, y_vec, v_ang);

	Mat m_mag, m_ang, x_mat, y_mat;
	cartToPolar(x_vec, y_vec, m_mag, m_ang);
	polarToCart(m_mag, m_ang, x_mat, y_mat);

	cout << "[x_vec] = " << ((Mat)x_vec).reshape(1, 1) << endl;
	cout << "[y_vec] = " << ((Mat)y_vec).reshape(1, 1) << endl;
	cout << "[v_mag] = " << ((Mat)v_mag).reshape(1, 1) << endl;
	cout << "[v_ang] = " << ((Mat)v_ang).reshape(1, 1) << endl;

	cout << "[m_mag] = " << m_mag << endl;
	cout << "[m_ang] = " << m_ang << endl;
	cout << "[x_mat] = " << x_mat << endl;
	cout << "[y_mat] = " << y_mat << endl;

	return 0;
}
