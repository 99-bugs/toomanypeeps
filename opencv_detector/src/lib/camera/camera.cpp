#include "camera.h"

namespace TooManyPeeps {

  Camera::Camera(void) {
    isDone = false;
  }

  Camera::~Camera(void) {

  }

  bool Camera::is_done(void) {
    return isDone;
  }

  void Camera::done(void) {
    isDone = true;
  }

};
