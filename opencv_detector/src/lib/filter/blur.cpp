#include "blur.h"

namespace TooManyPeeps {

  Blur::Blur(const cv::Mat& original, cv::Mat& result, int kernelSize)
    : ProcessFilter(original, result) {

    this->kernelSize = kernelSize;
  }

  void Blur::execute(void) {
    cv::blur(get_original(), get_result(), cv::Size(kernelSize, kernelSize));
  }

};
