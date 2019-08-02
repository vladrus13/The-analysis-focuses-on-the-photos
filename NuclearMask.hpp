#include <opencv2/core/mat.hpp>
#include "picture.hpp"

typedef std::vector<std::vector<std::bitset<kBitset>>> tmask;

void get_nucleus_mask(Picture & a, const long double &EPSDEPTH) {
	long double red_gradation = 0,
		green_gradation = 0,
		blue_gradation = 0;

	for (int32_t i = 0; i < a.get_blue.rows; i++) {
		for (int32_t j = 0; j < a.get_blue.cols; j++) {
			red_gradation += a.get_red.at(i, j);
			green_gradation += a.get_green.at(i, j);
			blue_gradation += a.get_blue.at(i, j);
		}
	}
	red_gradation /= a.get_blue.rows * a.get_blue.cols;
	green_gradation /= a.get_blue.rows * a.get_blue.cols;
	blue_gradation /= a.get_blue.rows * a.get_blue.cols;
	std::shared_ptr<tmask> returned = a.generate_empty_mask();
	for (int32_t i = 0; i < a.get_blue.rows; i++) {
		for (int32_t j = 0; j < a.get_blue.cols; j++) {
			if (abs(a.get_red.at(i, j) - red_gradation) < EPSDEPTH) a.get_red.at(i, j) = 0;
			if (abs(a.get_green.at(i, j) - green_gradation) < EPSDEPTH) a.get_green.at(i, j) = 0;
			if (abs(a.get_blue.at(i, j) - blue_gradation) < EPSDEPTH) a.get_blue.at(i, j) = 0;
			short med = (a.get_red.at(i, j) ? 1 : 0) + (a.get_green.at(i, j) ? 1 : 0) + (a.get_blue.at(i, j) ? 1 : 0);
			(*returned)[i][j / kBitset][j % kBitset] = (med < 2 ? 0 : 1);
		}
	}
	a.set_nucleus_mask(*returned);
}

