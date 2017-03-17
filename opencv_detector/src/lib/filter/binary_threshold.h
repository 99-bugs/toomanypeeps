#pragma once

#include "types/process_filter.h"

namespace TooManyPeeps {

  class BinaryThreshold : public ProcessFilter {

    private:
      static const int MAX_OUTPUT_VALUE = 255;

    private:
      int threshold;

    public:
      BinaryThreshold(const cv::Mat& original, cv::Mat& result, int threshold);

    public:
      virtual void execute(void);
  };

};