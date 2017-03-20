#pragma once

#include <opencv2/opencv.hpp>
#include "contour_finder.h"
#include "tracked_object.h"

namespace TooManyPeeps {

  class Tracker
  {
    private:
      static const int MAX_DELTA_DISTANCE = 24;
      ContourFinder contourFinder;
      std::vector<TrackedObject> trackedObjects;
      int currentLabelId;

    public:
      Tracker(void);
      ~Tracker(void);

    public:
      void find_contours(cv::Mat& image);
      void draw(cv::Mat & image);

    private:
      void add_contours_to_tracked_objects(void);
      void update_tracked_objects(void);
      void track(cv::Point2f referencePoint);
      size_t get_index_of_closest_object(cv::Point2f referencePoint);
      void process_reference_point(cv::Point2f referencePoint, TrackedObject & closestObject);
      void add_new_tracked_object(cv::Point2f referencePoint);
  };

};
