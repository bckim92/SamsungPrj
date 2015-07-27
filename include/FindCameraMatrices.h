#ifndef FINDCAMERAMATRIX_H
#define FINDCAMERAMATRIX_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace sfm {
	using namespace std;
	using namespace cv;

	void findCameraMatrix();
	void computeEssential(Mat imageL, Mat imageR, Mat camera, Mat &E);
	void EtoRandT(Mat E, Mat &U, Mat &V_t, Mat &W);
	bool CheckCoherentRotation(Mat_<double> &R);
	bool testTriangulation();
}

#endif
