#include "fake_raspi_cam.h"

namespace TooManyPeeps {

  namespace Fake {

    FakeRaspiCam::FakeRaspiCam(void) {}

    bool FakeRaspiCam::open(void) { return true; }
    bool FakeRaspiCam::isOpened() const { return true; }
    void FakeRaspiCam::release() {}
    bool FakeRaspiCam::grab() { return true; }
    void FakeRaspiCam::retrieve(cv::Mat& image) {}
    double FakeRaspiCam::get(int propId) { return 0.0; }
    bool FakeRaspiCam::set(int propId, double value) { return true; }
    std::string FakeRaspiCam::getId() const { return std::string(""); }
  };

};
