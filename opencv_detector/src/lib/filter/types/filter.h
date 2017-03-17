#pragma once

#include <opencv2/opencv.hpp>

namespace TooManyPeeps {

  class Filter {

    public:
      virtual void execute(void) = 0;

  };

};
