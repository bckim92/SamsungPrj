#ifndef UTILITY_H
#define UTILITY_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <vector>

namespace sfm {
	void listFiles(std::string dirname, std::vector<std::string> &filenames);
	void readFiles(std::vector<std::string> filenames, std::vector<cv::Mat> &images);
}

#endif
