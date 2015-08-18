CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
PROJECT(SmartCampus)
SET(MY_DIR ${PROJECT_SOURCE_DIR})

# Guard against in-source build
IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	MESSAGE(FATAL_ERROR "In-source build not allowed.")
ENDIF()

# Enabling c++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
IF(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSEIF(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
ELSE()
	MESSAGE(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
ENDIF()

# Dependencies
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(OpenMVG REQUIRED)
FIND_PACKAGE(Boost REQUIRED COMPONENTS filesystem)
FIND_PACKAGE(PCL 1.7 REQUIRED)

SET(INCLUDE_DIRS
	${OPENMVG_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
	"${MY_DIR}/include"
)

SET(LIBRARIES
	${OPENMVG_LIBRARIES}
	${OpenCV_LIBRARIES}
	${Boost_LIBRARIES}
	${PCL_LIBRARIES}
)

SET(SOURCES
	src/sfm/Utility.cpp
	src/sfm/Calibration.cpp
	src/sfm/FindCameraMatrices.cpp
	src/sfm/Triangulation.cpp
	src/sfm/Visualizer.cpp

	src/inertial/FrameProcessor.cpp
	src/inertial/InertialTracker.cpp
	src/inertial/ModelingProcessor.cpp
	src/inertial/PoseEstimator.cpp
)

SET(EXECUTABLE_OUTPUT_PATH ${MY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${MY_DIR}/lib)

LINK_DIRECTORIES(
	${Boost_LIBRARY_DIRS}
	${PCL_LIBRARY_DIRS}
)

ADD_DEFINITIONS(${PCL_DEFINITIONS})

ADD_LIBRARY(smartcampus OBJECT ${SOURCES})
set_target_properties(smartcampus PROPERTIES POSITION_INDEPENDENT_CODE 1)
ADD_LIBRARY(smartcampusshared SHARED $<TARGET_OBJECTS:smartcampus>)
ADD_LIBRARY(smartcampusstatic STATIC $<TARGET_OBJECTS:smartcampus>)
set_target_properties(smartcampusshared PROPERTIES OUTPUT_NAME smartcampus)
set_target_properties(smartcampusstatic PROPERTIES OUTPUT_NAME smartcampus)
MESSAGE("Linking with these libraries: ${LIBRARIES}")

INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(smartcampusshared ${LIBRARIES})

# Generate executables
ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main smartcampusshared)

ADD_EXECUTABLE(GlobalPipeline GlobalPipeline.cpp)
TARGET_LINK_LIBRARIES(GlobalPipeline smartcampusshared)

ADD_EXECUTABLE(SequentialPipeline SequentialPipeline.cpp)
TARGET_LINK_LIBRARIES(SequentialPipeline smartcampusshared)

ADD_EXECUTABLE(Calibration Calibration.cpp)
TARGET_LINK_LIBRARIES(Calibration smartcampusshared)

ADD_EXECUTABLE(InertialPipeline InertialPipeline.cpp)
TARGET_LINK_LIBRARIES(InertialPipeline smartcampusshared)
