#include <iostream>
#include <string>
#include <sys/stat.h>

using namespace std;

const string OPENMVG_SFM_BIN = "~/openMVG/build/software/SfM";
const string CAMERA_SENSOR_WIDTH_DIRECTORY = "~/Desktop/SamsungPrj/resource/cameraSensorWidth";
struct stat info;

int main (int argc, char **argv) {
	if (argc < 3) {
		cout << "Usage " << argv[0] << " image_dir output_dir" << endl;
		return 0;
	}

	string input_dir(argv[1]);
	string output_dir(argv[2]);
	string matches_dir = output_dir + "/matches";
	string reconstruction_dir = output_dir + "/reconstruction_global";
	string camera_file_params = CAMERA_SENSOR_WIDTH_DIRECTORY + "/cameraGenerated.txt";

	cout << "Using input dir  : " << input_dir << endl;
	cout << "      output dir : " << output_dir << endl;

	if (stat(output_dir.c_str(), &info) != 0 || !S_ISDIR(info.st_mode))
		mkdir(output_dir.c_str(), S_IRWXU);
	if (stat(matches_dir.c_str(), &info) != 0 || !S_ISDIR(info.st_mode))
		mkdir(matches_dir.c_str(), S_IRWXU);
	
	cout << "1. Instrinsics analysis" << endl;
	string image_listing = OPENMVG_SFM_BIN + "/openMVG_main_SfMInit_ImageListing -i " + input_dir + " -o " + matches_dir + " -d " + camera_file_params;
	system(image_listing.c_str());

	cout << "2. Compute features" << endl;
	string compute_features = OPENMVG_SFM_BIN + "/openMVG_main_ComputeFeatures -i " + matches_dir + "/sfm_data.json -o " + matches_dir + " -m SIFT";
	system(compute_features.c_str());

	cout << "3. Compute matches" << endl;
	string compute_matches = OPENMVG_SFM_BIN + "/openMVG_main_ComputeMatches -i " + matches_dir + "/sfm_data.json -o " + matches_dir + " -r 0.8 -g e";
	system(compute_matches.c_str());

	if (stat(reconstruction_dir.c_str(), &info) != 0 || !S_ISDIR(info.st_mode))
		mkdir(reconstruction_dir.c_str(), S_IRWXU);
	
	cout << "4. Do Global reconstruction" << endl;
	string global_reconstruction = OPENMVG_SFM_BIN + "/openMVG_main_GlobalSfM -i " + matches_dir + "/sfm_data.json -m " + matches_dir + " -o " + reconstruction_dir;
	system(global_reconstruction.c_str());

	cout << "5. Colorize Structure" << endl;
	string colorize = OPENMVG_SFM_BIN + "/openMVG_main_ComputeSfM_DataColor -i " + reconstruction_dir + "/sfm_data.json -o " + reconstruction_dir + "/colorized.ply";

	cout << "6. Structure from Known Poses (robust triangulation)" << endl;
	string sfm_robust = OPENMVG_SFM_BIN + "/openMVG_main_ComputeStructureFromKnownPoses -i " + reconstruction_dir + "/sfm_data.json -m " + matches_dir + " -f " + matches_dir + "/matches.e.txt -o " + reconstruction_dir + "/robust.json";
	system(sfm_robust.c_str());

	string colorize_robust = OPENMVG_SFM_BIN + "/openMVG_main_ComputeSfM_DataColor -i " + reconstruction_dir + "/robust.json -o " + reconstruction_dir + "/robust_colorized.ply";
	system(colorize_robust.c_str());
	return 0;
}
