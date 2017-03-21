#pragma once

#include "types/process_filter.h"
#include "../tracking/tracker.h"
#include "find_contours.h"

namespace TooManyPeeps {

  class TrackObjects : public ProcessFilter {

    private:
      FindContours * contoursFilter;
      Tracker tracker;

    public:
      TrackObjects(const cv::Mat& original, cv::Mat& result, FindContours * contoursFilter, CounterCallback callback);

    public:
      virtual void execute(void);

  };

};
