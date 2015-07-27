#include <Triangulation.h>

namespace sfm {
	using namespace std;
	using namespace cv;
	
	Mat_<double> LinearLSTriangulation(
			Point3d u,
			Matx34d P,
			Point3d u1,
			Matx34d P1) {
		//build A matrix
		Matx43d A(u.x*P(2,0)-P(0,0),u.x*P(2,1)-P(0,1),u.x*P(2,2)-P(0,2),
				  u.y*P(2,0)-P(1,0),u.y*P(2,1)-P(1,1),u.y*P(2,2)-P(1,2),
				  u1.x*P1(2,0)-P1(0,0), u1.x*P1(2,1)-P1(0,1),u1.x*P1(2,2)-P1(0,2),
				  u1.y*P1(2,0)-P1(1,0), u1.y*P1(2,1)-P1(1,1),u1.y*P1(2,2)-P1(1,2)
				  );

		//build B vector
		Matx41d B(-(u.x*P(2,3)-P(0,3)),
				  -(u.y*P(2,3)-P(1,3)),
				  -(u1.x*P1(2,3)-P1(0,3)),
				  -(u1.y*P1(2,3)-P1(1,3)));

		//solve for X
		Mat_<double> X;
		solve(A,B,X,DECOMP_SVD);
		return X;
	}

	double TriangulatePoints(
			const vector<KeyPoint> &pt_set1,
			const vector<KeyPoint> &pt_set2,
			const Mat &Kinv,
			const Matx34d &P,
			const Matx34d &P1,
			vector<Point3d> &pointcloud) {
		vector<double> reproj_error;
		unsigned int pts_size = pt_set1.size();
		for (unsigned int i = 0; i < pts_size; ++i) {
			// convert to normalized homogeneous coordinates
			Point2f kp = pt_set1[i].pt;
			Point3d u(kp.x, kp.y, 1.0);
			Mat_<double> um = Kinv * Mat_<double>(u);
			// u = um.at<Point3d>(0);? or...
			u.x = um(0);
			u.y = um(1);
			u.z = um(2);
			Point2f kp1 = pt_set2[i].pt;
			Point3d u1(kp1.x, kp1.y, 1.0);
			Mat_<double> um1 = Kinv * Mat_<double>(u1);
			// u1 = um1.at<Point3d>(0);? or...
			u1.x = um1(0);
			u1.y = um1(1);
			u1.z = um1(2);

			// triangulate
			Mat_<double> X = LinearLSTriangulation(u, P, u1, P1);

			// reprojection error
			Mat_<double> xPt_img = K * Mat(P1) * X;
			Point2f xPt_img_(xPt_img(0)/xPt_img(2),xPt_img(1)/xPt_img(2));
			reproj_error.push_back(norm(xPt_img_ - kp1));

			// store 3D point
			pointcloud.push_back(Point3d(X(0), X(1), X(2)));
		}

		Scalar me = mean(reproj_error);
		return me[0];
	}
}
