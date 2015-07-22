#ifndef UTILITY_H
#define UTILITY_H

#include "openMVG/image/image.hpp"

#include <string>
#include <vector>

namespace sfm {
	typedef openMVG::image::Image<openMVG::image::RGBColor> RGB;

	void listFiles(std::string dirname, std::vector<std::string> &filenames);
	void readFiles(std::vector<std::string> filenames, std::vector<RGB> &images);
}

#endif
