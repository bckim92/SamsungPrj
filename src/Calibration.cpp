#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/opencv.hpp"

#include <iostream>
#include <vector>
#include <string>

#include "Calibration.h"

namespace sfm {
	using namespace std;
	using namespace cv;

	void writeCalibration(vector<string> filenames, float squareSize, int height, int width) {
		Size boardSize(height, width);
		vector<bool> success(filenames.size());
		vector<vector<Point2f>> corners(filenames.size());

		for (int i = 0; i < filenames.size(); ++i) {
			Mat image = imread(filenames[i],0);
			success[i] = findChessboardCorners(image, boardSize, corners[i],
					CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
		}

		vector<Point3f> chessboard;
		for (int i = 0; i < boardSize.height; ++i) {
			for (int j = 0; j < boardSize.width; ++j) {
				chessboard.push_back(Point3f(i * squareSize, j * squareSize, 0));
			}
		}

		vector<vector<Point2f>> imagePoints;
		vector<vector<Point3f>> objectPoints;
		vector<Mat> cimg, rvecs, tvecs;

		for (int i = 0; i < filenames.size(); ++i) {
			if (success[i]) {
				imagePoints.push_back(corners[i]);
				objectPoints.push_back(chessboard);
				cout << "Chess board found in " << filenames[i] << endl;
			}
		}

		Mat cameraMatrix = Mat::eye(3,3,CV_64F);
		Mat distCoeffs = Mat::zeros(5,1,CV_64F);
		Mat baseImage = imread(filenames[0]);

		calibrateCamera(objectPoints, imagePoints, baseImage.size(),
						cameraMatrix, distCoeffs, rvecs, tvecs,
						CV_CALIB_FIX_ASPECT_RATIO
						+ CV_CALIB_ZERO_TANGENT_DIST
						+ CV_CALIB_FIX_K1
						+ CV_CALIB_FIX_K2
						+ CV_CALIB_FIX_K3
						);

		FileStorage fs("data/calibration.xml", CV_STORAGE_WRITE);
		fs << "cameraMatrix" << cameraMatrix;
		fs << "distCoeffs" << distCoeffs;
		fs.release();
	}

	void readCalibration() {
		Mat cameraMatrix;
		Mat distCoeffs;

		FileStorage fs("data/calibration.xml", CV_STORAGE_READ);
		fs["cameraMatrix"]>>cameraMatrix;
		fs["distCoeffs"]>>distCoeffs;
		fs.release();
	}
}
