#pragma once

#include <opencv2/opencv.hpp>

namespace TooManyPeeps {

  class FrameGrabber
  {
    private:
      bool isDone;

    public:
      FrameGrabber(void);
      virtual ~FrameGrabber(void);

    public:
      virtual cv::Mat grab_frame(void) = 0;

    public:
      bool is_done(void);

    protected:
      void done(void);

  };

};
