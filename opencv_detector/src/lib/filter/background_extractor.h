#pragma once

#include "types/process_filter.h"

namespace TooManyPeeps {

  class BackgroundExtractor : public ProcessFilter {

    private:
      static const bool TRACK_SHADOWS = true;

    private:
      cv::Ptr<cv::BackgroundSubtractor> backgroundExtractor;

    public:
      BackgroundExtractor(const cv::Mat& original, cv::Mat& result, int historySize=100, double threshold=16);
      BackgroundExtractor(cv::Mat& image, int historySize=100, double threshold=16);
      ~BackgroundExtractor(void);

    public:
      virtual void execute(void);
  };

};
