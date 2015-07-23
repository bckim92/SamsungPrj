#include "openMVG/image/image.hpp"

#include <string>
#include <vector>

#include "utility.h"
#include "calibration.h"

typedef openMVG::image::Image<openMVG::image::RGBColor> RGB;

int main(int argc, char **argv) {
	std::vector<std::string> filenames;

	if (argc > 1) {
		sfm::listFiles(std::string(argv[1]), filenames);
	} else {
		std::cout << "\nusage: main [path]" << std::endl;
		return -1;
	}

	std::vector<RGB> images;
	sfm::readFiles(filenames, images);
	//sfm::writeCalibration(filenames, 1.0f, 9, 6);
	sfm::readCalibration();

	return 0;
}
