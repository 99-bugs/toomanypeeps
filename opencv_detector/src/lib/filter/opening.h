#pragma once

#include "types/process_filter.h"
#include "erode.h"
#include "dilate.h"

namespace TooManyPeeps {

  class Opening : public ProcessFilter {

    private:
      Erode erode;
      Dilate dilate;

    public:
      Opening(const cv::Mat& original, cv::Mat& result, int kernelSize=5);
      Opening(cv::Mat& image, int kernelSize=5);

    public:
      virtual void execute(void);
  };

};
