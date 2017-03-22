#include "track_objects.h"

namespace TooManyPeeps {

  // Original is actually not needed here because
  // tracker gets its data from FindContours filter
  // [REFACTOR] To be better we should actually create an abstract Input and Output
  // class and inherit from this for both Mat and Contours.
  // This would however probable need templates
  TrackObjects::TrackObjects(const cv::Mat& original, cv::Mat& result,
    FindContours * contoursFilter, CounterCallback callback)
    : ProcessFilter(original, result) {

    tracker.register_counter_callback(callback);
    this->contoursFilter = contoursFilter;
  }

  void TrackObjects::execute(void) {
    std::vector<cv::Point2f> blobReferences = contoursFilter->get_object_reference_points();
    tracker.update(blobReferences);
    tracker.draw(get_result());
  }

};
