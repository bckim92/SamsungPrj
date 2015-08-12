#ifndef FINDCAMERAMATRIX_H
#define FINDCAMERAMATRIX_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

namespace sfm {
	using namespace std;
	using namespace cv;

	bool findCameraMatrix(
			Mat imageL,
			Mat imageR,
			Mat K,
			Matx34d &P0,
			Matx34d &P1,
			vector<KeyPoint> &pt_set0,
			vector<KeyPoint> &pt_set1);
	bool CheckCoherentRotation(Mat_<double> &R);
	void DecomposeEtoRandT(
			Mat E,
			Mat_<double> &R1,
			Mat_<double> &R2,
			Mat_<double> &t1,
			Mat_<double> &t2);
	bool TestTriangulation();
}

#endif
