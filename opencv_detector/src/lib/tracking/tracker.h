#pragma once

#include <opencv2/opencv.hpp>
#include "contour_finder.h"
#include "tracked_object.h"

namespace TooManyPeeps {

  class Tracker
  {
    private:
      int maxDeltaDistance;
      std::vector<TrackedObject> trackedObjects;
      int currentLabelId;

      int topReference;
      int bottomReference;

    public:
      Tracker(int maxDeltaDistance=24);
      ~Tracker(void);

    public:
      void update(const std::vector<cv::Point2f> & blobReferences);
      void draw(cv::Mat & image);

    private:
      void add_to_tracked_objects(const std::vector<cv::Point2f> & blobReferences);
      void update_tracked_objects(void);
      void track(cv::Point2f referencePoint);
      size_t get_index_of_closest_object(cv::Point2f referencePoint);
      void process_reference_point(cv::Point2f referencePoint, TrackedObject & closestObject);
      void add_new_tracked_object(cv::Point2f referencePoint);

    private:
      void draw_references(cv::Mat & image);
  };

};
