#pragma once
#include <opencv2/imgproc.hpp>
#include <bitset>
#include <memory>
const int kBitset = 8;
class Picture {
    typedef std::vector<std::vector<std::bitset<kBitset>>> tmask;
    cv::Mat red_;
    cv::Mat green_;
    cv::Mat blue_;
    tmask nucleus_mask_;
public:
    explicit Picture(const cv::Mat &red, const cv::Mat &green, const cv::Mat &blue);
	explicit Picture(cv::Mat&& red, cv::Mat&& green, cv::Mat&& blue);
	Picture();
    const cv::Mat &get_red();
    const cv::Mat &get_green();
    const cv::Mat &get_blue();
    std::shared_ptr<tmask> generate_empty_mask();
    void set_nucleus_mask(std::vector<std::vector<std::bitset<kBitset>>> mask);
    const tmask &get_nucleus_mask();
    bool is_nucleus(int x, int y);
    friend std::ostream& operator<<(std::ostream& os, const Picture& dt);
};