#pragma once

#include <opencv2/opencv.hpp>
#include <string>

namespace TooManyPeeps {

  namespace Fake {

    class FakeRaspiCam {

      public:
        FakeRaspiCam(void);

      public:
        bool open(void);
        bool isOpened() const;
        void release();
        bool grab();
        void retrieve(cv::Mat& image);
        double get(int propId);
        bool set(int propId, double value);
        std::string getId() const;
    };

  };

};
