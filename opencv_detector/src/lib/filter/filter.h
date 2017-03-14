#pragma once

#include <opencv2/opencv.hpp>

namespace TooManyPeeps {

  class Filter {
    private:
      const cv::Mat& original;
      cv::Mat& result;

    public:
      Filter(const cv::Mat& original, cv::Mat& result);
      virtual ~Filter(void);

    public:
      virtual void execute(void) = 0;

    protected:
      const cv::Mat& get_original(void);
      cv::Mat& get_result(void);

  };

};
