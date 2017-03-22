#pragma once

#include <opencv2/opencv.hpp>

namespace TooManyPeeps {

  class TrackedObject
  {
    private:
      static const int TIME_TO_LIVE = 3;
      std::vector<cv::Point2f> positions;
      int timeToLive;
      int id;
      bool hasBeenReported;

    public:
      TrackedObject(cv::Point2f currentLocation);

    public:
      cv::Point2f get_last_known_location(void);
      void add_current_location(cv::Point2f location);
      void set_id(int id);
      int get_id(void);
      cv::Point2f get_start_location(void);

    public:
      void decrement_time_to_live(void);
      bool is_alive(void);
      void indicate_as_reported(void);
      bool is_reported(void);

    private:
      void reset_time_to_live(void);

    public:
      double distance_from(TrackedObject & object);
      double distance_from(const cv::Point2f & point);
      std::string to_string(void);
      void draw_history(cv::Mat & image);
  };

};
