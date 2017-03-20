#include "background_extractor.h"

namespace TooManyPeeps {

  BackgroundExtractor::BackgroundExtractor(const cv::Mat& original, cv::Mat& result,
    int historySize, double threshold)
    : ProcessFilter(original, result) {

    backgroundExtractor = cv::createBackgroundSubtractorMOG2(historySize, threshold, TRACK_SHADOWS);
    // If TRACK_SHADOWS = true, shadows are also marked in result with value = 127
  }

  BackgroundExtractor::~BackgroundExtractor(void) {
    delete backgroundExtractor;
  }

  void BackgroundExtractor::execute(void) {
    backgroundExtractor->apply(get_original(), get_result());
  }

};
