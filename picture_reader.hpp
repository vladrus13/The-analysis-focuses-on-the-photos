#pragma once

#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>
#include "picture.hpp"

namespace Reader {
	class picture_reader {
		const std::string path_;
	public:
		explicit picture_reader(const std::string location);
		void read(Picture& output, const std::string name);
	private:
		static void correction(cv::Mat& source);
	};

	void get_images(std::vector <Picture>& pictures);
};
