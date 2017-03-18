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

};
