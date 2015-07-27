#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include <string>
#include <iostream>

#include "FindCameraMatrices.h"

namespace sfm {
	using namespace std;
	using namespace cv;

	void findCameraMatrix() {
	}

	void computeEssential(Mat imageL, Mat imageR, Mat camera, Mat &E) {
		// Detect the keypoints
		ORB detector;
		vector<KeyPoint> keypointsL, keypointsR;
		Mat descriptorsL, descriptorsR;
		detector(imageL, noArray(), keypointsL, descriptorsL);
		detector(imageR, noArray(), keypointsR, descriptorsR);
		
		// Matching descriptor vectors
		BFMatcher matcher(NORM_HAMMING);
		vector<DMatch> matches;
		matcher.match(descriptorsL, descriptorsR, matches);

		double max_dist = 0;
		double min_dist = 100;
		int matches_size = matches.size();

		for (int i = 0; i < matches_size; ++i) {
			double dist = matches[i].distance;
			if (dist < min_dist)
				min_dist = dist;
			if (dist > max_dist)
				max_dist = dist;
		}

		vector<DMatch> good_matches;
		for (int i = 0; i < matches_size; ++i) {
			if (matches[i].distance < 3*min_dist)
				good_matches.push_back(matches[i]);
		}

		vector<Point2f> pointsL, pointsR;

		for (int i = 0; i < good_matches.size(); ++i) {
			pointsL.push_back(keypointsL[good_matches[i].queryIdx].pt);
			pointsR.push_back(keypointsR[good_matches[i].trainIdx].pt);
		}

		Mat fundamental = findFundamentalMat(pointsL, pointsR, FM_RANSAC, 3, 0.99);
		E = camera.t() * fundamental * camera.t();
	}

	void EtoRandT(Mat E, Mat &U, Mat &V_t, Mat &W) {
		// SVD decomposition
		SVD svd = SVD(E);
		U = svd.u;
		V_t = svd.vt;

		Matx33d W(0,-1,0
				  1,0,0,
				  0,0,1);

		Mat_<double> R = svd.u * Mat(W) * svd.vt;
		Mat_<double> t = svd.u.col(2);

		if (CheckCoherentRotation(R)) {
			Matx34d P0(1,0,0,0,
					   0,1,0,0,
					   0,0,1,0);
			Matx34d P1(R(0,0),R(0,1),R(0,2),t(0),
					   R(1,0),R(1,1),R(1,2),t(1),
					   R(2,0),R(2,1),R(2,2),t(2));
		} else {
		}
	}

	bool CheckCoherentRotation(Mat_<double> &R) {
		if (fabsf(determinant(R)) - 1.0 > 1e-07) {
			cerr<<"det(R) != +-1.0, this is not a rotation matrix"<<endl;
			return false;
		}
		return true;
	}

	bool testTriangulation() {
	}
}
