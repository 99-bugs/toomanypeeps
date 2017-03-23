#include "ip_camera.h"

namespace TooManyPeeps {

  IPCamera::IPCamera(std::string streamAddress)
  {
    std::cout << "Opening IP Camera @" << streamAddress << std::endl;
    if (!captureDevice.open(streamAddress)) {
      std::cerr << "Error opening IP camera" << std::endl;
      throw std::exception();
    }
  }

  IPCamera::~IPCamera(void) {
    captureDevice.release();
  }

  cv::Mat IPCamera::grab_frame(void) {
    cv::Mat frame;
    captureDevice.read(frame);
    return frame;
  }

};
