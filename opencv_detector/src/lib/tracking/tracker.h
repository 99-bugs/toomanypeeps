#pragma once

#include <opencv2/opencv.hpp>
#include "contour_finder.h"

namespace TooManyPeeps {

  class Tracker
  {
    private:
      ContourFinder contourFinder;

    public:
      Tracker(void);
      ~Tracker(void);

    public:
      void find_contours(cv::Mat& image, cv::Mat& original);
  };

};
