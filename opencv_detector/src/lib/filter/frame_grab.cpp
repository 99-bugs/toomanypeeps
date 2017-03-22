#include "frame_grab.h"

namespace TooManyPeeps {

  FrameGrab::FrameGrab(cv::Mat& result, FrameGrabber * frame_grabber)
    : OutputFilter(result) {
    this->frame_grabber = frame_grabber;
  }

  void FrameGrab::execute(void) {
    cv::Mat frame = frame_grabber->grab_frame();
    frame.copyTo(get_result());
  }

};
