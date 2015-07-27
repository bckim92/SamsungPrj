#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <vector>
#include <string>

namespace sfm {
	void writeCalibration(std::vector<std::string> filenames);
	void writeCalibration(std::vector<std::string> filenames, float squareSize, int height, int width);
	void readCalibration();
}

#endif
