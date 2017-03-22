#include "opening.h"

namespace TooManyPeeps {

  Opening::Opening(const cv::Mat& original, cv::Mat& result, int kernelSize)
    : ProcessFilter(original, result),
      erode(original, result, kernelSize),
      dilate(result, result, kernelSize) {
  }

  Opening::Opening(cv::Mat& image, int kernelSize)
    : Opening(image, image, kernelSize) {
  }

  void Opening::execute(void) {
    erode.execute();
    dilate.execute();
  }

};
