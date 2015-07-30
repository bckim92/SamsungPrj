#include <sstream>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include "Visualizer.h"

namespace sfm {
	using namespace std;
	using namespace pcl;
	using namespace cv;

	void Visualizer::spinOnce(vector<Point3d> points) {
		stringstream ss;
		ss << counter;

		PointCloud<PointXYZRGB>::Ptr cloud(new PointCloud<PointXYZRGB>);
		for (int i = 0; i < points.size(); ++i){
			PointXYZRGB point;
			point.x = points[i].x;
			point.y = points[i].y;
			point.z = points[i].z;
			cout << "x : " << point.x << " y : " << point.y << " z : " << point.z << endl;
			cloud->points.push_back(point);
		}

		viewer->addPointCloud<PointXYZRGB>(cloud, ss.str());
		viewer->setPointCloudRenderingProperties(visualization::PCL_VISUALIZER_POINT_SIZE, 1, ss.str());
		viewer->spin();
	}
}
