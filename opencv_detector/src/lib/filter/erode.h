#pragma once

#include "types/process_filter.h"

namespace TooManyPeeps {

  class Erode : public ProcessFilter {

    private:
      cv::Mat kernel;

    public:
      Erode(const cv::Mat& original, cv::Mat& result, int kernelSize=3);
      Erode(cv::Mat& image, int kernelSize=3);

    public:
      virtual void execute(void);
  };

};
