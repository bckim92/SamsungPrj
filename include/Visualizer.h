#ifndef VISUALIZER_H
#define VISUALIZER

#include <opencv2/core/core.hpp>

#include <pcl/visualization/pcl_visualizer.h>

#include <vector>

namespace sfm {
	using namespace std;
	using namespace cv;
	using namespace pcl;
	class Visualizer {
		public:
			Visualizer() {
				visualization::PCLVisualizer::Ptr pcl_viewer(new visualization::PCLVisualizer("3D Viewer"));
				viewer = pcl_viewer;
				viewer->setBackgroundColor(0, 0, 0);
			};
			~Visualizer(){};
			void spinOnce(vector<Point3d> points);
		private:
			visualization::PCLVisualizer::Ptr viewer;
			int counter = 0;
	};
}

#endif
