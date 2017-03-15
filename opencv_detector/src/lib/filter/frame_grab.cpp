#include "frame_grab.h"

namespace TooManyPeeps {

  FrameGrab::FrameGrab(cv::Mat& result, Camera * camera)
    : OutputFilter(result) {
    this->camera = camera;
  }

  void FrameGrab::execute(void) {
    cv::Mat frame = camera->grab_frame();
    frame.copyTo(get_result());
  }

};
