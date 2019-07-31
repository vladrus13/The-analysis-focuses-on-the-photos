#include "picture.hpp"
#include <opencv2/imgproc.hpp>
#include <utility>
#include <iostream>

Picture::Picture(cv::Mat red, cv::Mat green, cv::Mat blue) : red_(std::move(red)), green_(std::move(green)), blue_(std::move(blue)) {}

const cv::Mat & Picture::get_red() {
    return red_;
}

const cv::Mat & Picture::get_green() {
    return green_;
}

const cv::Mat & Picture::get_blue() {
    return blue_;
}
typedef std::vector<std::vector<std::bitset<kBitset>>> tmask;

std::shared_ptr<tmask> Picture::generate_empty_mask() {
    auto cols = red_.cols / 8 + 1;
    auto rows = red_.rows;
    auto * mask = new tmask(rows);
    for (int i = 0; i < rows; i++) {
        (*mask)[i].assign(cols, 0);
    }
    return std::make_shared<tmask>(*mask);
}
const std::vector<std::vector<std::bitset<8>>> & Picture::get_nucleus_mask() {
    return nucleus_mask_;
}

void Picture::set_nucleus_mask(std::vector<std::vector<std::bitset<8>>> mask) {
    nucleus_mask_ = std::move(mask);
}

bool Picture::is_nucleus(int x, int y) {
    auto cols = y / kBitset;
    auto shift = y % kBitset;
    auto rows = x / kBitset;
    return nucleus_mask_[rows][cols][shift];
}

std::ostream &operator<<(std::ostream &os, const Picture &pic) {
    os << "Red: " << pic.red_ << "\n" << "Green: " << pic.green_ << "\n" << "Blue: " << pic.green_ << "\n";
    return os;
}