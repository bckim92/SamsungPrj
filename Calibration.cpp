#include <opencv2/core/core.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "sfm/Utility.h"
#include "sfm/Calibration.h"

using namespace std;

int main (int argc, char **argv) {
	if (argc < 3) {
		cout << "Usage " << argv[0] << " image_dir output_dir" << endl;
		return 0;
	}

	string input_dir(argv[1]);
	string output_dir(argv[2]);

	cout << "Using input dir  : " << input_dir << endl;
	cout << "      output dir : " << output_dir << endl;
	
	vector<string> filenames;
	vector<cv::Mat> images;

	sfm::listFiles(input_dir, filenames);
	sfm::readFiles(filenames, images);

	cv::Mat K, distCoeffs;
	sfm::writeCalibration(filenames, 1.0f, 9, 6);

	return 0;
}
