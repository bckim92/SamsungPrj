#include "openMVG/image/image.hpp"
#include "openMVG/features/akaze/AKAZE.hpp"

#include "openMVG/matching/matcher_brute_force.hpp"
#include "openMVG/matching/matching_filters.hpp"

#include <string>
#include <iostream>

#include "feature_and_matching.h"

namespace sfm {
	using namespace std;
	using namespace openMVG;
	using namespace openMVG::image;
	using namespace openMVG::matching;

	typedef Image<RGBColor> RGB;
	typedef Descriptor<float, 64> Descriptor_T;

	void computeFeatures(RGB imageL, RGB imageR) {
		vector<SIOPointFeature> featureL, featureR;
		AKAZEConfig options;
		vector<Descriptor_T> descL, descR;

		// Detect Feature
		AKAZEDetector<Descriptor_T::bin_type, 64>(imageL, featureL, descL, options);
		AKAZEDetector<Descriptor_T::bin_type, 64>(imageR, featureR, descR, options);

		showFeatures(imageL, imageR, featureL, featureR);

		// Perform Matching
	}

	void matchFeatures() {
	}

	void sfmSolving() {
	}

	void showFeatures(RGB imageL, RGB imageR, vector<SIOPointFeature> featureL, vector<SIOPointFeature> featureR) {
		RGB concat;
		ConcatH(imageL, imageR, concat);

		// Draw features
		for (size_t i = 0; i < featureL.size(); ++i) {
			SIOPointFeature &imaA = featureL[i];
			DrawCircle(imaA.x(), imaA.y(), imaA.scale(), 255, &concat);
		}

		for (size_t i = 0; i < featureR.size(); ++i) {
			SIOPointFeature &imaB = featureL[i];
			DrawCircle(imaB.x(), imaB.y(), imaB.scale(), 255, &concat);
		}
		string out_filename = "result/features.jpg";
		WriteImage(out_filename.c_str(), concat);
	}

	void showMatches() {
	}
}
