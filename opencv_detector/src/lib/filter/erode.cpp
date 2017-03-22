#include "erode.h"

namespace TooManyPeeps {

  Erode::Erode(const cv::Mat& original, cv::Mat& result, int kernelSize)
    : ProcessFilter(original, result) {

    kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE,
      cv::Size(2*kernelSize + 1, 2*kernelSize+1), cv::Point(kernelSize, kernelSize));
  }

  Erode::Erode(cv::Mat& image, int kernelSize)
    : Erode(image, image, kernelSize) {
  }

  void Erode::execute(void) {
    cv::erode(get_original(), get_result(), kernel);
  }

};
