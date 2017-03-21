#include "tracker.h"

#include <vector>
#include "contour_finder.h"
#include "comparators/compare_object_distance.h"

namespace TooManyPeeps {

  Tracker::Tracker(void)
    : contourFinder(5000, 50000) {

    trackedObjects.clear();
    currentLabelId = 0;
  }

  Tracker::~Tracker(void) {
  }

  void Tracker::find_contours(cv::Mat& image) {
    contourFinder.find(image);
    add_contours_to_tracked_objects();
    update_tracked_objects();
  }

  void Tracker::add_contours_to_tracked_objects(void) {
    std::vector<cv::Point2f> objectCenters = contourFinder.get_object_reference_points();

    for (size_t i = 0; i < objectCenters.size(); i++) {
      track(objectCenters[i]);
    }
  }

  void Tracker::update_tracked_objects(void) {
    for (size_t i = 0; i < trackedObjects.size(); i++) {
      trackedObjects[i].decrement_time_to_live();
      if (!trackedObjects[i].is_alive()) {
        trackedObjects.erase(trackedObjects.begin()+i);
      }
    }
  }

  void Tracker::track(cv::Point2f referencePoint) {
    if (trackedObjects.empty()) {
      add_new_tracked_object(referencePoint);
      return;
    }

    int indexClosestObject = get_index_of_closest_object(referencePoint);
    std::cout << "Closest object = " << trackedObjects[indexClosestObject].get_id() << std::endl;
    process_reference_point(referencePoint, trackedObjects[indexClosestObject]);
  }

  size_t Tracker::get_index_of_closest_object(cv::Point2f referencePoint) {
    std::vector<double> distances;
    for (size_t i = 0; i < trackedObjects.size(); i++) {
      distances.push_back(trackedObjects[i].distance_from(referencePoint));
    }

    std::vector<size_t> indicesOfObjectsSortedByDistance;
    for (size_t i = 0; i < trackedObjects.size(); i++) {
      indicesOfObjectsSortedByDistance.push_back(i);
    }

    // Is this correct ? Shit yeah it is
    std::sort(indicesOfObjectsSortedByDistance.begin(), indicesOfObjectsSortedByDistance.end(),
      CompareObjectDistance(distances));

    return indicesOfObjectsSortedByDistance[0];
  }

  void Tracker::process_reference_point(cv::Point2f referencePoint, TrackedObject & closestObject) {
    if (closestObject.distance_from(referencePoint) <= MAX_DELTA_DISTANCE) {
      std::cout << "Matching based on distance = " << closestObject.distance_from(referencePoint) << std::endl;
      closestObject.add_current_location(referencePoint);
    } else {
      add_new_tracked_object(referencePoint);
    }
  }

  void Tracker::add_new_tracked_object(cv::Point2f referencePoint) {
    std::cout << "Adding new object" << std::endl;
    TrackedObject object(referencePoint);
    object.set_id(currentLabelId++);
    trackedObjects.push_back(object);
  }

  void Tracker::draw(cv::Mat & image) {
    contourFinder.draw(image);

    if (trackedObjects.size() > 0) {
      std::cout << std::endl << "TRACKED:" << std::endl;
      for (size_t i = 0; i < trackedObjects.size(); i++) {
        std::cout << trackedObjects[i].to_string() << std::endl;
        trackedObjects[i].draw_history(image);
      }
    }
  }
};
