#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "openMVG/image/image.hpp"

#include <vector>

namespace sfm {
	typedef openMVG::image::Image<openMVG::image::RGBColor> RGB;

	void calibration(std::vector<RGB> images);
}

#endif
