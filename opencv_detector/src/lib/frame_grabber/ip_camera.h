#pragma once

#include "frame_grabber.h"
#include <string>

namespace TooManyPeeps {

  class IPCamera : public FrameGrabber
  {
    private:
      cv::VideoCapture captureDevice;

    public:
      IPCamera(std::string streamAddress);
      virtual ~IPCamera(void);

    public:
      virtual cv::Mat grab_frame(void);

  };

};
