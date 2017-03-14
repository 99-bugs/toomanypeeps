#include "filter.h"

namespace TooManyPeeps {

  Filter::Filter(const cv::Mat& original, cv::Mat& result)
    : original(original), result(result) {

  }

  Filter::~Filter(void) {}

  const cv::Mat& Filter::get_original(void) {
    return original;
  }

  cv::Mat& Filter::get_result(void) {
    return result;
  }

};
