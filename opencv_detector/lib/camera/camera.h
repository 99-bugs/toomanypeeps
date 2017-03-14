#pragma once

#include <opencv2/opencv.hpp>

namespace TooManyPeeps {

  class Camera
  {
    private:
      bool isDone;

    public:
      Camera(void);

    public:
      virtual cv::Mat grab_frame(void) = 0;

    public:
      bool is_done(void);

    protected:
      void done(void);

  };

};
