#include "openMVG/image/image.hpp"

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem.hpp"
#include <iostream>
#include <string>
#include <vector>

#include "utility.h"

namespace sfm {
	namespace fs = boost::filesystem;
	typedef openMVG::image::Image<openMVG::image::RGBColor> RGB;

	void listFiles(std::string dirname, std::vector<std::string> &filenames) {
		fs::path full_path(fs::initial_path<fs::path>());
		full_path = fs::system_complete(fs::path(dirname));

		if (!fs::exists(full_path)) {
			std::cout << "\nNot found: " << dirname << std::endl;
			return;
		}

		unsigned long file_count = 0;
		unsigned long dir_count = 0;
		unsigned long other_count = 0;
		unsigned long err_count = 0;

		if (fs::is_directory(full_path)) {
			std::cout << "\nIn directory: " << dirname << "\n\n";
			fs::directory_iterator end_itr;
			for (fs::directory_iterator dir_itr(full_path); dir_itr != end_itr; ++dir_itr) {
				try {
					if (fs::is_directory(dir_itr->status())) {
						++dir_count;
						std::cout << dir_itr->path().filename() << " [directory]\n";
					} else if (fs::is_regular_file(dir_itr->status())) {
						++file_count;
						filenames.push_back(dirname + "/" + dir_itr->path().filename().string());
						std::cout << dir_itr->path().filename() << "\n";
					} else {
						++other_count;
						std::cout << dir_itr->path().filename() << " [other]\n";
					}
				} catch (const std::exception &ex) {
					++err_count;
					std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
				}
			}
			std::cout << "\n" << file_count << " files\n"
			          << dir_count << " directories\n"
					  << other_count << " others\n"
					  << err_count << " erros\n";
		}
	}

	void readFiles(std::vector<std::string> filenames, std::vector<RGB> &images) {
		for (int i = 0; i < filenames.size(); ++i) {
			RGB image;
			char filename[filenames[i].size()+1];
			strcpy(filename, filenames[i].c_str());
			std::cout<<filename<<std::endl;
			openMVG::image::ReadImage(filename, &image);
			images.push_back(image);
		}
	}
}
