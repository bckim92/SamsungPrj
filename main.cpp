#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <vector>
#include <iostream>

#include "utility.h"
#include "calibration.h"

int main(int argc, char **argv) {
	std::vector<std::string> filenames;

	if (argc > 1) {
		sfm::listFiles(std::string(argv[1]), filenames);
	} else {
		std::cout << "\nusage: main [path]" << std::endl;
		return -1;
	}

	std::vector<cv::Mat> images;
	sfm::readFiles(filenames, images);
	sfm::writeCalibration(filenames, 1.0f, 9, 6);
	//sfm::readCalibration();

	return 0;
}
