#pragma once

#include "filter.h"
#include "../camera/camera.h"

namespace TooManyPeeps {

  class FrameGrab : public Filter {
    private:
      Camera * camera;

    public:
      FrameGrab(cv::Mat& result, Camera * camera);

    public:
      virtual void execute(void);
  };

};
