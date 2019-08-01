#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <utility>
#include "picture_reader.hpp"

picture_reader::picture_reader(const std::string location) : path_(location) {}

void picture_reader::read(Picture& output, const std::string name) {
	cv::Mat source_red = cv::imread(path_ + name + "_red.tif", 0);
	cv::Mat source_green = cv::imread(path_ + name + "_green.tif", 0);
	cv::Mat source_blue = cv::imread(path_ + name + "_blue.tif", 0);
	correction(source_red);
	correction(source_green);
	correction(source_blue);
	output = Picture(std::move(source_red), std::move(source_green), std::move(source_blue));
}

void picture_reader::correction(cv::Mat& source) {
	double minimum, maximum;
	cv::minMaxLoc(source, &minimum, &maximum);
	std::cout << minimum << ' ' << maximum << '\n';
	double alpha = 255.0 / (maximum - minimum);
	double beta = -alpha * minimum;
	source.convertTo(source, -1, alpha, beta);
}

