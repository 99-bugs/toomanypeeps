#pragma once

#include "filter.h"

namespace TooManyPeeps {

  class FilterChain {

    private:
      std::vector<Filter*> filters;

    public:
      FilterChain(void);
      ~FilterChain(void);

    public:
      void add(Filter * filter);
      void execute(void);

  };

};
