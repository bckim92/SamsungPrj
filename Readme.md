# Dependency
	* OpenCV
	* OpenMVG
	* Boost
	* PCL

# Installation Guide
## Install OpenCV
	sudo apt-get install libopencv-dev
## Install OpenMVG
	https://raw.githubusercontent.com/openMVG/openMVG/master/BUILD
## Install Boost
	sudo apt-get install libboost-all-dev
## Install PCL
	sudo add-apt-repository ppa:v-launchpad-jochen-sprickerhof-de/pcl
	sudo apt-get update
	sudo apt-get install libpcl-all

# Build Instruction
	mkdir build 
	cd build
	cmake ..
	make
