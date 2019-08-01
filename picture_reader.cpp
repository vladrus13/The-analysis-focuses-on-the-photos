#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <utility>
#include "picture_reader.hpp"

Reader::picture_reader::picture_reader(const std::string location) : path_(location) {}

void Reader::picture_reader::read(Picture& output, const std::string name) {
	cv::Mat source_red = cv::imread(path_ + name + "_red.tif", 0);
	cv::Mat source_green = cv::imread(path_ + name + "_green.tif", 0);
	cv::Mat source_blue = cv::imread(path_ + name + "_blue.tif", 0);
	correction(source_red);
	correction(source_green);
	correction(source_blue);
	output = Picture(std::move(source_red), std::move(source_green), std::move(source_blue));
}

void Reader::picture_reader::correction(cv::Mat& source) {
	double minimum, maximum;
	cv::minMaxLoc(source, &minimum, &maximum);
	std::cout << minimum << ' ' << maximum << '\n';
	double alpha = 255.0 / (maximum - minimum);
	double beta = -alpha * minimum;
	source.convertTo(source, -1, alpha, beta);
}

 void Reader::get_images(std::vector<Picture>& pictures) {
	picture_reader reader("../images\\");
	std::vector<std::string> filenames;
	cv::glob("../images/*_blue.tif", filenames, false);
	pictures.resize(filenames.size());
	for (int i = 0; i < filenames.size(); i++) {
		size_t first_pos = filenames[i].find_last_of('\\') + 1;
		size_t last_pos = filenames[i].find_last_of('_');
		reader.read(pictures[i], filenames[i].substr(first_pos, last_pos - first_pos));
	}
}
