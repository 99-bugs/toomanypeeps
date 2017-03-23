#include "display.h"

namespace TooManyPeeps {

  Display::Display(const cv::Mat& original, std::string windowTitle)
    : InputFilter(original) {
      this->windowTitle = windowTitle;
      this->magnification = magnification;

    cv::namedWindow(windowTitle, cv::WINDOW_NORMAL);
    cv::resizeWindow(windowTitle, 320, 240);
  }

  void Display::execute(void) {
    cv::imshow(windowTitle, get_original());
    cv::waitKey(10);
  }

};
