#pragma once

#include "types/process_filter.h"

namespace TooManyPeeps {

  class Erode : public ProcessFilter {

    private:
      cv::Mat kernel;

    public:
      Erode(const cv::Mat& original, cv::Mat& result, int kernelSize);

    public:
      virtual void execute(void);
  };

};
