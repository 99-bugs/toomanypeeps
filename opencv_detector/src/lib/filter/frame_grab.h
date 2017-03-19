#pragma once

#include "types/output_filter.h"
#include "../frame_grabber/frame_grabber.h"

namespace TooManyPeeps {

  class FrameGrab : public OutputFilter {
    private:
      FrameGrabber * frame_grabber;

    public:
      FrameGrab(cv::Mat& result, FrameGrabber * frame_grabber);

    public:
      virtual void execute(void);
  };

};
