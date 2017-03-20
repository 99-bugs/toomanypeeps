#include "tracker.h"

#include <vector>
#include "contour_finder.h"

namespace TooManyPeeps {

  Tracker::Tracker(void)
    : contourFinder(5000, 50000) {
  }

  Tracker::~Tracker(void) {
  }

  void Tracker::find_contours(cv::Mat& image, cv::Mat& original) {
    contourFinder.find(image);
    contourFinder.draw(original);

    cv::imshow("Contours", original);
    cv::waitKey(100);
  }

};
