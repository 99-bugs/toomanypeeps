#include "pi_camera.h"

namespace TooManyPeeps {

  PiCamera::PiCamera(void)
  {
    captureDevice.set(CV_CAP_PROP_FORMAT, CV_8UC1);

    std::cout << "Opening Rpi Camera..." << std::endl;
    if (!captureDevice.open()) {
      std::cerr << "Error opening Rpi camera" << std::endl;
      throw std::exception();
    }

    set_width(640);
    set_height(480);
    grey_mode();
    set_framerate(5);
  }

  PiCamera::~PiCamera(void) {
    captureDevice.release();
  }

  cv::Mat PiCamera::grab_frame(void) {
    cv::Mat frame;

    captureDevice.grab();
    captureDevice.retrieve (frame);

    return frame;
  }

  void PiCamera::set_width(int width) {
    captureDevice.set(CV_CAP_PROP_FRAME_WIDTH, width);
  }

  void PiCamera::set_height(int height) {
    captureDevice.set(CV_CAP_PROP_FRAME_HEIGHT, height);
  }

  void PiCamera::set_framerate(int framesPerSecond) {
    captureDevice.set(CV_CAP_PROP_FPS, framesPerSecond);
  }

  void PiCamera::color_mode(void) {
    captureDevice.set(CV_CAP_PROP_FORMAT, CV_8UC3);
  }

  void PiCamera::grey_mode(void) {
    captureDevice.set(CV_CAP_PROP_FORMAT, CV_8UC1);
  }
};
