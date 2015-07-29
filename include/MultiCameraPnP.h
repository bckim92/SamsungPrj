#ifndef MULTICAMERAPNP_H
#define MULTICAMERAPNP_H

#include <vector>

namespace sfm {
	using namespace cv;
	using namespace std;

	struct CloudPoint {
		Point3d pt;
		vector<int> index_of_2d_origin;
	};
}

#endif
