#include "tracked_object.h"

#include <sstream>
#include "../helpers/color_generator.h"

namespace TooManyPeeps {

  TrackedObject::TrackedObject(cv::Point2f currentLocation) {
    add_current_location(currentLocation);
    reset_time_to_live();
    id = -1;
  }

  cv::Point2f TrackedObject::get_last_known_location(void) {
    return positions.back();
  }

  cv::Point2f TrackedObject::get_start_location(void) {
    return positions.front();
  }

  void TrackedObject::add_current_location(cv::Point2f location) {
    positions.push_back(location);
    reset_time_to_live();
  }

  void TrackedObject::set_id(int id) {
    this->id = id;
  }

  int TrackedObject::get_id(void) {
    return id;
  }

  double TrackedObject::distance_from(TrackedObject & object) {
    return distance_from(object.get_last_known_location());
  }

  double TrackedObject::distance_from(const cv::Point2f & point) {
    return cv::norm(point-get_last_known_location());
  }

  void TrackedObject::reset_time_to_live(void) {
    timeToLive = TIME_TO_LIVE;
  }

  void TrackedObject::decrement_time_to_live(void) {
    timeToLive--;
  }

  bool TrackedObject::is_alive(void) {
    return (timeToLive > 0);
  }

  std::string TrackedObject::to_string(void) {
    std::stringstream ss;
    ss << "ID = " << id << " TTL = " << timeToLive << " #tracked = " << positions.size();
    return ss.str();
  }

  void TrackedObject::draw_history(cv::Mat & image) {
    int thickness = 2;

    for (size_t i = 0; i < positions.size()-1; i++) {
      if (i+1 == positions.size()-1) {
        thickness = 4;
      }
      cv::line(image, positions[i], positions[i+1], ColorGenerator::yellow(), thickness);
    }
  }
};
