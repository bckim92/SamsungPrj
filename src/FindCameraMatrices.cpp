#include "opencv2/calib3d/calib3d.hpp"

#include <string>
#include <iostream>

#include "FindCameraMatrices.h"

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
			vector<KeyPoint> &pt_set1) {
		cout << "Find camera matrix..." << endl;
		// Detect the keypoints
		ORB detector;
		vector<KeyPoint> keypointsL, keypointsR;
		Mat descriptorsL, descriptorsR;
		detector(imageL, noArray(), keypointsL, descriptorsL);
		detector(imageR, noArray(), keypointsR, descriptorsR);
		pt_set0 = keypointsL;
		pt_set1 = keypointsR;
		
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

		// Select good matches
		vector<DMatch> good_matches;
		for (int i = 0; i < matches_size; ++i) {
			if (matches[i].distance < 3*min_dist)
				good_matches.push_back(matches[i]);
		}

		if (good_matches.size() < 10) {
			cerr << "not enough inliers after F matrix" << endl;
			return false;
		}

		vector<Point2f> pointsL, pointsR;

		for (int i = 0; i < good_matches.size(); ++i) {
			pointsL.push_back(keypointsL[good_matches[i].queryIdx].pt);
			pointsR.push_back(keypointsR[good_matches[i].trainIdx].pt);
		}

		// Compute essential matrix
		Mat F = findFundamentalMat(pointsL, pointsR, FM_RANSAC, 3, 0.99);
		Mat E = K.t() * F * K.t();

		if (fabsf(determinant(E)) > 1e-07) {
			cout << "det(E) != 0 : " << determinant(E) << endl;
			P0 = 0;
			P1 = 0;
			return false;
		}

		cout << "K : " << K << endl;
		cout << "good match size : " << good_matches.size() << endl;

		// SVD decomposition
		Mat_<double> R1,R2,t1,t2;
		DecomposeEtoRandT(E,R1,R2,t1,t2);

		if (determinant(R1) + 1.0 < 1e-09) {
			cout << "det(R) == -1 [" << determinant(R1) << "]: flip E's sign" << endl;
			DecomposeEtoRandT(-E,R1,R2,t1,t2);
		}

		if (!CheckCoherentRotation(R1)) {
			cout << "resulting rotation is not coherent\n" << endl;
			P0 = 0;
			P1 = 0;
			return false;
		}

		Matx34d p0(1,0,0,0,
				 0,1,0,0,
				 0,0,1,0);
		// TODO : select answer from 4 cases
		Matx34d p1(R1(0,0),R1(0,1),R1(0,2),t1(0),
				 R1(1,0),R1(1,1),R1(1,2),t1(1),
				 R1(2,0),R1(2,1),R1(2,2),t1(2));

		P0 = p0;
		P1 = p1;

		cout << "P0 : " << P0 << endl;
		cout << "P1 : " << P1 << endl;

		return true;
	}

	bool CheckCoherentRotation(Mat_<double> &R) {
		if (fabsf(determinant(R)) - 1.0 > 1e-07) {
			cerr<<"det(R) != +-1.0, this is not a rotation matrix"<<endl;
			return false;
		}
		return true;
	}

	void DecomposeEtoRandT(
			Mat E,
			Mat_<double> &R1,
			Mat_<double> &R2,
			Mat_<double> &t1,
			Mat_<double> &t2){
		SVD svd = SVD(E);

		Matx33d W(0,-1,0,
				  1,0,0,
				  0,0,1);
		Matx33d Wt(0,1,0,
				   -1,0,0,
				   0,0,1);

		R1 = svd.u * Mat(W) * svd.vt;
		R2 = svd.u * Mat(Wt) * svd.vt;
		t1 = svd.u.col(2);
		t2 = -svd.u.col(2);
	}

	bool testTriangulation(
			const vector<Point3d> &pointcloud,
			const Matx34d &P,
			vector<uchar> &status
			) {
		vector<Point3d> pointcloud_pt3d
	}
}
