# CMake Bulid File
#
# CMake Version
cmake_minimum_required(VERSION 3.12)

# Compiler Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER_ID MSVC)

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Zc:preprocessor -MDd")
	add_compile_options("/wd4251" "/MDd" "/Zc:twoPhase-" "/Zc:__cplusplus")
endif()

message(STATUS "\n-- ------------------------------------------------------------------------------------------------------")
message(STATUS "Building Listpi3D with ${CMAKE_CXX_COMPILER_ID} using flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "------------------------------------------------------------------------------------------------------\n--")

# Set the project name
project(Listpi3D)

add_subdirectory(opencv)

add_executable(
	Listpi3D
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(
	Listpi3D
	PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/opencv/include
	${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/calib3d/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/cudaarithm/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/cudabgsegm/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/cudacodec/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/cudafeatures2d/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/cudafilters/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/cudaimgproc/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/cudalegacy/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/cudaobjdetect/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/cudaoptflow/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/cudastereo/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/cudawarping/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/cudev/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/dnn/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/features2d/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/flann/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/highgui/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/imgcodecs/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/imgproc/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/ml/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/objdetect/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/photo/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/shape/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/stitching/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/superres/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/ts/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/video/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/videoio/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/videostab/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/viz/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opencv/modules/world/include
)

target_link_libraries(Listpi3D opencv_core opencv_highgui opencv_imgproc)