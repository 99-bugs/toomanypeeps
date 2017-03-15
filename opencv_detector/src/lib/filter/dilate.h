#pragma once

#include "types/process_filter.h"

namespace TooManyPeeps {

  class Dilate : public ProcessFilter {

    private:
      cv::Mat kernel;

    public:
      Dilate(const cv::Mat& original, cv::Mat& result, int kernelSize);

    public:
      virtual void execute(void);
  };

};
