#include "tracker.h"

#include <vector>
#include "contour_finder.h"
#include "comparators/compare_object_distance.h"
#include "../helpers/color_generator.h"

namespace TooManyPeeps {

  Tracker::Tracker(int maxDeltaDistance) {
    trackedObjects.clear();
    currentLabelId = 0;
    this->maxDeltaDistance = maxDeltaDistance;

    this->topReference = 50;    // pixels from top
    this->bottomReference = 130; // pixels from bottom

    currentlyInsideCounter = 0;
    updateCallback = false;

    counterCallback = nullptr;
  }

  Tracker::~Tracker(void) {
  }

  void Tracker::update(const std::vector<cv::Point2f> & blobReferences) {
    add_to_tracked_objects(blobReferences);
    update_tracked_objects();
  }

  void Tracker::add_to_tracked_objects(const std::vector<cv::Point2f> & blobReferences) {
    for (size_t i = 0; i < blobReferences.size(); i++) {
      track(blobReferences[i]);
    }
  }

  void Tracker::update_tracked_objects(void) {
    for (size_t i = 0; i < trackedObjects.size(); i++) {
      trackedObjects[i].decrement_time_to_live();

      Direction direction = determine_direction_of_tracked_object(trackedObjects[i]);
      if (direction == GOING_IN) {
        increment_in();
      } else if (direction == GOING_OUT) {
        increment_out();
      }

      if (!trackedObjects[i].is_alive()) {
        trackedObjects.erase(trackedObjects.begin()+i);
      }
    }

    // Do it once per frame
    if (updateCallback) {
      send_current_counter();
    }
  }

  Direction Tracker::determine_direction_of_tracked_object(TrackedObject & object) {
    Direction direction = UNKNOWN;

    if (object.get_start_location().y <= topReference
      && object.get_last_known_location().y >= bottomReference) {
        direction = GOING_OUT;
    } else if (object.get_start_location().y >= bottomReference
      && object.get_last_known_location().y <= topReference) {
        direction = GOING_IN;
    }

    return direction;
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
    if (closestObject.distance_from(referencePoint) <= maxDeltaDistance) {
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
    if (trackedObjects.size() > 0) {
      std::cout << std::endl << "TRACKED:" << std::endl;
      for (size_t i = 0; i < trackedObjects.size(); i++) {
        std::cout << trackedObjects[i].to_string() << std::endl;
        trackedObjects[i].draw_history(image);
      }
    }
    draw_references(image);
    draw_counter(image);
  }

  void Tracker::draw_references(cv::Mat & image) {
    int thickness = 3;
    cv::line(image, cv::Point(0, topReference), cv::Point(image.cols, topReference), ColorGenerator::lime(), thickness);
    cv::line(image, cv::Point(0, bottomReference), cv::Point(image.cols, bottomReference), ColorGenerator::lime(), thickness);
  }

  void Tracker::draw_counter(cv::Mat & image) {
    char buffer[200];
    sprintf(buffer, "Number of people inside: %d", currentlyInsideCounter);
    cv::Point2f where(20, image.rows-20);
    double scale = 1;
    cv::putText(image, buffer, where, cv::FONT_HERSHEY_PLAIN, scale, ColorGenerator::cyan(), 2);
  }

  void Tracker::increment_in(void) {
    currentlyInsideCounter++;
    updateCallback = true;
  }

  void Tracker::increment_out(void) {
    currentlyInsideCounter--;
    updateCallback = true;
  }

  void Tracker::register_counter_callback(CounterCallback callback) {
    this->counterCallback = callback;
  }

  void Tracker::send_current_counter(void) {
    if (counterCallback != nullptr) {
      counterCallback(currentlyInsideCounter);
    }
    updateCallback = false;
  }
};
