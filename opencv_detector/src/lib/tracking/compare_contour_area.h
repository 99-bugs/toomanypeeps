#pragma once

#include <vector>

namespace TooManyPeeps {

  struct CompareContourArea
  {
    const std::vector<double> & areas;

    CompareContourArea(const std::vector<double> & areas)
      : areas(areas) {
    }

    bool operator()(size_t left, size_t right) const {
      return areas[left] > areas[right];
    }

  };

};
