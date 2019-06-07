#include "pch.h"
#include "Study10WarpingCamera.h"


Study10WarpingCamera::Study10WarpingCamera()
{
}


Study10WarpingCamera::~Study10WarpingCamera()
{
}

int Study10WarpingCamera::Start()
{
	string path = "D:\\Dev\\Study\\Open CV 영상처리_학습자용\\교재예제\\10장_예제\\image\\";

	Size boardSize(8, 7), imageSize;
	float squareSize = 1.f;

	vector<String> fileList;
	fileList.push_back(path + "chessboard_01.jpg");
	fileList.push_back(path + "chessboard_02.jpg");
	fileList.push_back(path + "chessboard_03.jpg");

	vector<vector<Point2f>> imagePoints;
	vector<vector<Point3f>> objectPoints;

	for (int i = 0; i < fileList.size(); i++)
	{
		Mat image = imread(fileList[i], 1);
		CV_Assert(image.data);

		vector<Point2f> imgPoints = findImageCorners(image, boardSize);

		if (!imgPoints.empty())
		{
			vector<Point3f> objPoints = calcObjectCorners(boardSize, squareSize);
			imagePoints.push_back(imgPoints);
			objectPoints.push_back(objPoints);
		}
	}

	vector<Mat> rvecs, tvecs;
	Mat cameraMatrix, distCoeffs;
	Mat undistorted;

	Mat image = imread(path + "chessboard_05.jpg", 1);
	CV_Assert(image.data);

	double rms = calibrateCamera(objectPoints, imagePoints, image.size(), cameraMatrix, distCoeffs, rvecs, tvecs);
	undistort(image, undistorted, cameraMatrix, distCoeffs);

	cout << "camera Matrix " << endl << cameraMatrix << endl << endl;
	printf("RMS error reported by cailbrateCamera: %g\n", rms);

	imshow("Original", image);
	imshow("Undistorted", undistorted);
	waitKey();

	return 0;
}

vector<Point2f> Study10WarpingCamera::findImageCorners(Mat image, Size boardSize)
{
	static int cnt = 0;
	vector<Point2f> imgPoints;
	Mat gray;
	cvtColor(image, gray, COLOR_RGB2GRAY);

	bool found = findChessboardCorners(gray, boardSize, imgPoints);

	if (found)
	{
		cornerSubPix(gray, imgPoints, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 30, 0.1));
		drawChessboardCorners(image, boardSize, imgPoints, found);
		imshow("image_" + to_string(cnt), image);
		waitKey();
		destroyWindow("image_" + to_string(cnt++));
	}

	return imgPoints;
}

vector<Point3f> Study10WarpingCamera::calcObjectCorners(Size boardSize, float squareSize)
{
	vector<Point3f> corners;

	for (int i = 0; i < boardSize.height; i++)
	{
		for (int j = 0; j < boardSize.width; j++)
		{
			float x = float(j * squareSize);
			float y = float(i * squareSize);
			corners.push_back(Point3f(x, y, 0));
		}
	}

	return corners;
}
