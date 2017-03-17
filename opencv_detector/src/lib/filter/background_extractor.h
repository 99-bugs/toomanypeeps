#pragma once

#include "types/process_filter.h"

namespace TooManyPeeps {

  class BackgroundExtractor : public ProcessFilter {

    private:
      static const bool TRACK_SHADOWS = false;

    private:
      cv::Ptr<cv::BackgroundSubtractor> backgroundExtractor;

    public:
      BackgroundExtractor(const cv::Mat& original, cv::Mat& result, int historySize, double threshold);
      ~BackgroundExtractor(void);

    public:
      virtual void execute(void);
  };

};
