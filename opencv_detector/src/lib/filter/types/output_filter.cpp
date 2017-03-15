#include "output_filter.h"

namespace TooManyPeeps {

  OutputFilter::OutputFilter(cv::Mat& result)
    : result(result) {

  }

  cv::Mat& OutputFilter::get_result(void) {
    return result;
  }

};
