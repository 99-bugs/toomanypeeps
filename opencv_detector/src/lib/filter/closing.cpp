#include "closing.h"

namespace TooManyPeeps {

  Closing::Closing(const cv::Mat& original, cv::Mat& result, int kernelSize)
    : ProcessFilter(original, result),
      dilate(original, result, kernelSize),
      erode(result, result, kernelSize) {

  }

  Closing::Closing(cv::Mat& image, int kernelSize)
    : Closing(image, image, kernelSize) {
  }

  void Closing::execute(void) {
    dilate.execute();
    erode.execute();
  }

};
