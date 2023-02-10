#include <dirent.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

// A function to calculate the normal map from a set of images
cv::Mat calcNormalMap(const std::vector<cv::Mat>& images, const cv::Vec3f& lightDirection) {
	int		rows = images[0].rows;
	int		cols = images[0].cols;

	cv::Mat normalMap(rows, cols, CV_32FC3);
	cv::Mat I = cv::Mat::zeros(rows * cols, images.size(), CV_32FC1);

	// Fill the I matrix with the pixel intensities from each image
	for(int i = 0; i < images.size(); i++) {
		cv::Mat image = images[i];
		image.reshape(1, rows * cols).copyTo(I.col(i));
	}

	// Solve for the normal map
	cv::Mat n;
	cv::solve(I, cv::Mat(rows * cols, 3, CV_32FC1, lightDirection), n, cv::DECOMP_SVD);
	n = n.reshape(3, rows);

	// Normalize the normals
	cv::normalize(n, normalMap);

	return normalMap;
}

std::vector<std::string> readImagesFromFolder(std::string folder) {
	std::vector<std::string> filenames;
	DIR*					 dir;
	struct dirent*			 ent;
	if((dir = opendir(folder.c_str())) != NULL) {
		while((ent = readdir(dir)) != NULL) {
			std::string file_name = ent->d_name;
			std::string ext		  = file_name.substr(file_name.find_last_of(".") + 1);
			if(ext == "jpg" || ext == "jpeg" || ext == "png") filenames.push_back(folder + "/" + file_name);
		}
		closedir(dir);
	} else {
		cout << "Could not open directory" << endl;
	}
	return filenames;
}

int main(int argc, char** argv) {
	// Load the set of images
	std::vector<cv::Mat>	 images;
	std::string				 folder	   = "C:\Users\\Alpas\\OneDrive\\Desktop\\New folder";
	std::vector<std::string> filenames = readImagesFromFolder(folder);
	for(int i = 0; i < filenames.size(); i++) {
		images.push_back(cv::imread(filenames[i], cv::IMREAD_GRAYSCALE));
		if(!image.empty()) {
			cout << "Image loaded successfully: " << filenames[i] << endl;
		} else {
			cout << "Error: Could not load image " << filenames[i] << endl;
		}
	}

	// Specify the light directions (for example purposes, we'll use 4 lights positioned at the cardinal directions)
	std::vector<cv::Vec3f> lightDirections = {cv::Vec3f(1, 0, 0), cv::Vec3f(-1, 0, 0), cv::Vec3f(0, 1, 0), cv::Vec3f(0, -1, 0)};

	// Calculate the normal map for each light direction
	std::vector<cv::Mat>   normalMaps;
	for(const cv::Vec3f& lightDirection : lightDirections) {
		normalMaps.push_back(calcNormalMap(images, lightDirection));
	}

	// Merge the normal maps into a single normal map
	cv::Mat normalMap = cv::Mat::zeros(images[0].rows, images[0].cols, CV_32FC3);
	for(const cv::Mat& nm : normalMaps) {
		normalMap += nm;
	}
	normalMap /= normalMaps.size();

	// Perform 3D reconstruction using the normal map
	// ...

	return 0;
}
