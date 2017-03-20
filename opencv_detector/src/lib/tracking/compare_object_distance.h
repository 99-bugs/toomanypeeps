//Based on: http://stackoverflow.com/questions/1723066/c-stl-custom-sorting-one-vector-based-on-contents-of-another

#pragma once

#include <vector>

namespace TooManyPeeps {

  struct CompareObjectDistance : std::binary_function<size_t, size_t, bool>
  {
    const std::vector<double> & _distances;

    CompareObjectDistance(const std::vector<double> & distances)
      : _distances(distances) {
    }

    bool operator()(size_t left, size_t right) const {
      return _distances[left] < _distances[right];
    }

  };

};
