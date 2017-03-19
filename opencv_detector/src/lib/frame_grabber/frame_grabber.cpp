#include "frame_grabber.h"

namespace TooManyPeeps {

  FrameGrabber::FrameGrabber(void) {
    isDone = false;
  }

  FrameGrabber::~FrameGrabber(void) {

  }

  bool FrameGrabber::is_done(void) {
    return isDone;
  }

  void FrameGrabber::done(void) {
    isDone = true;
  }

};
