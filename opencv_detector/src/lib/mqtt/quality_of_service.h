#pragma once

namespace TooManyPeeps {

  namespace Mqtt {

    enum QualityOfService
    {
      AT_MOST_ONCE = 0,
      AT_LEAST_ONCE = 1,
      EXACTLY_ONCE = 2
    };

  }

};
