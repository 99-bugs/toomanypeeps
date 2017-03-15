#include "binary_threshold.h"

namespace TooManyPeeps {

  BinaryThreshold::BinaryThreshold(const cv::Mat& original, cv::Mat& result, int threshold)
    : ProcessFilter(original, result) {
    this->threshold = threshold;
  }

  void BinaryThreshold::execute(void) {
    cv::threshold(get_original(), get_result(), threshold, MAX_OUTPUT_VALUE, cv::THRESH_BINARY);
  }

};
