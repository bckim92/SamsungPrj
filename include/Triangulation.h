#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <vector>

namespace sfm {
	using namespace cv;

	void TriangulatePoints(
			const vector<KeyPoint> &pt_set1,
			const vector<KeyPoint> &pt_set2,
			const Matx34d &P,
			const Matx34d &P1,
			vector<Point3d> &pointcloud);
}

#endif
