#pragma once

#include "frame_grabber.h"

namespace TooManyPeeps {

  class VideoFile : public FrameGrabber
  {
    private:
      cv::VideoCapture videoFile;

    public:
      VideoFile(std::string filename);
      virtual ~VideoFile(void);

    public:
      virtual cv::Mat grab_frame(void);

  };

};
