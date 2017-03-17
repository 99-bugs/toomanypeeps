#pragma once

#include "camera.h"

namespace TooManyPeeps {

  class WebCamera : public Camera
  {
    private:
      cv::VideoCapture captureDevice;

    public:
      WebCamera(void);
      virtual ~WebCamera(void);

    public:
      virtual cv::Mat grab_frame(void);

  };

};
