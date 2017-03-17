#include "gaussian_blur.h"

namespace TooManyPeeps {

  GaussianBlur::GaussianBlur(const cv::Mat& original, cv::Mat& result, double blurFactor, int kernelSize)
    : ProcessFilter(original, result) {
    this->kernelSize = kernelSize;
    this->blurFactor = blurFactor;
  }

  void GaussianBlur::execute(void) {
    cv::GaussianBlur(get_original(), get_result(), cv::Size(kernelSize, kernelSize), blurFactor, blurFactor);
  }

};
