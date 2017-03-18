#pragma once

#include "camera.h"

#ifdef USE_RASPBERRY_PI
  #include <raspicam/raspicam_cv.h>
#else
  #include "fake/fake_raspi_cam.h"
#endif

namespace TooManyPeeps {

  class PiCamera : public Camera
  {
    private:
    #ifdef USE_RASPBERRY_PI
      #pragma message ("Creating Raspi CAM device")
      raspicam::RaspiCam_Cv captureDevice;
    #else
      #pragma message ("Creating FAKE Raspi CAM device")
      Fake::FakeRaspiCam captureDevice;
    #endif

    public:
      PiCamera(void);
      virtual ~PiCamera(void);

    public:
      virtual cv::Mat grab_frame(void);

  };

};
