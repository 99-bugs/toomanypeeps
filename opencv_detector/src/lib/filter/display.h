#pragma once

#include "types/input_filter.h"

namespace TooManyPeeps {

  class Display : public InputFilter {

    private:
      std::string windowTitle;
      double magnification;

    public:
      Display(const cv::Mat& original, std::string windowTitle);

    public:
      virtual void execute(void);
  };

};
