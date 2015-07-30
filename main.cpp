#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <vector>
#include <iostream>

#include "Utility.h"
#include "Calibration.h"
#include "FindCameraMatrices.h"
#include "Triangulation.h"
#include "Visualizer.h"

bool calib_bool = false;

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

	// Camera calibration
	cv::Mat K, distCoeffs;
	if (calib_bool) {
		sfm::writeCalibration(filenames, 1.0f, 9, 6);
		return 0;
	} else
		sfm::readCalibration(K, distCoeffs);

	// Calculate Camera matrix
	cv::Matx34d P0, P1;
	std::vector<cv::KeyPoint> keypointsL, keypointsR;
	sfm::findCameraMatrix(
			images[1],
			images[2],
			K,
			P0,
			P1,
			keypointsL,
			keypointsR);

	// Triangulation
	std::vector<cv::Point3d> pointcloud;
	sfm::TriangulatePoints(keypointsL,keypointsR,P0,P1,pointcloud);

	// Visualization
	sfm::Visualizer *visualizer(new sfm::Visualizer());
	visualizer->spinOnce(pointcloud);

	return 0;
}
