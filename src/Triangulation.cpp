#include <iostream>

#include <Triangulation.h>

namespace sfm {
	using namespace std;
	using namespace cv;
	
	void TriangulatePoints(
			const vector<KeyPoint> &pt_set1,
			const vector<KeyPoint> &pt_set2,
			const Matx34d &P0,
			const Matx34d &P1,
			vector<Point3d> &pointcloud) {
		cout << "Triangulate points...";

		// Change point type
		vector<Point2f> pointsL, pointsR;
		for (int i = 0; i < pt_set1.size(); ++i) {
			pointsL.push_back(pt_set1[i].pt);
			pointsR.push_back(pt_set2[i].pt);
		}

		Mat X;
		triangulatePoints(P0,P1,pointsL,pointsR,X);

		for (int i = 0; i < pt_set1.size(); ++i) {
			float x = X.at<float>(0,i);
			float y = X.at<float>(1,i);
			float z = X.at<float>(2,i);
			float w = X.at<float>(3,i);
			//cout << "x : " << x << " y : " << y << " z : " << z << " w : " << w << endl;

			pointcloud.push_back(Point3d(x/w,y/w,z/w));
		}
	}
}
