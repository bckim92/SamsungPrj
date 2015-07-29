#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/opencv.hpp>

#include <vector>
#include <string>

namespace sfm {
	using namespace std;
	using namespace cv;

	void writeCalibration(vector<string> filenames);
	void writeCalibration(vector<string> filenames, float squareSize, int height, int width);
	void readCalibration(Mat &K, Mat &distCoeffs);
}

#endif
