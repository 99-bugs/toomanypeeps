#include "find_contours.h"

namespace TooManyPeeps {

  FindContours::FindContours(const cv::Mat& original, cv::Mat& result, double minimumArea, double maximumArea)
    : ProcessFilter(original, result), contourFinder(minimumArea, maximumArea) {
  }

  void FindContours::execute(void) {
    contourFinder.find(get_original());
    contourFinder.draw(get_result());
  }

  std::vector<cv::Point2f> FindContours::get_object_reference_points(void) {
    return contourFinder.get_object_reference_points();
  }

};
