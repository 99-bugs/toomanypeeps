#include "dilate.h"

namespace TooManyPeeps {

  Dilate::Dilate(const cv::Mat& original, cv::Mat& result, int kernelSize)
    : ProcessFilter(original, result) {

    kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE,
      cv::Size(2*kernelSize + 1, 2*kernelSize+1), cv::Point(kernelSize, kernelSize));
  }

  void Dilate::execute(void) {
    cv::dilate(get_original(), get_result(), kernel);
  }

};
