#pragma once

#include "types/process_filter.h"
#include "../tracking/contour_finder.h"

namespace TooManyPeeps {

  class FindContours : public ProcessFilter {

    private:
      ContourFinder contourFinder;

    public:
      FindContours(const cv::Mat& original, cv::Mat& result, double minimumArea=5000, double maximumArea=11000);

    public:
      virtual void execute(void);

    public:
      std::vector<cv::Point2f> get_object_reference_points(void);
  };

};
