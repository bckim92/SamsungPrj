#ifndef UTILITY_H
#define UTILITY_H

#include "openMVG/image/image.hpp"
#include "openMVG/features/akaze/AKAZE.hpp"

namespace sfm {
	using namespace std;
	using namespace openMVG;
	using namespace openMVG::image;

	typedef Image<RGBColor> RGB;
	typedef Descriptor<float, 64> Descriptor_T;

	void computeFeatures(RGB imageL, RGB imageR);
	void matchFeatures();
	void sfmSolving();
	void showFeatures(RGB imageL, RGB imageR, vector<SIOPointFeature> featureL, vector<SIOPointFeature> featureR);
	void showMatches();
}

#endif
