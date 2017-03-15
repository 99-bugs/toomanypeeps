#pragma once

#include "types/output_filter.h"
#include "../camera/camera.h"

namespace TooManyPeeps {

  class FrameGrab : public OutputFilter {
    private:
      Camera * camera;

    public:
      FrameGrab(cv::Mat& result, Camera * camera);

    public:
      virtual void execute(void);
  };

};
