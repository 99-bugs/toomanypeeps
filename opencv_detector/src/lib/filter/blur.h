#pragma once

#include "types/process_filter.h"

namespace TooManyPeeps {

  class Blur : public ProcessFilter {

    private:
      int kernelSize;

    public:
      Blur(const cv::Mat& original, cv::Mat& result, int kernelSize);

    public:
      virtual void execute(void);
  };

};
