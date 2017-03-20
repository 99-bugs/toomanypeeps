#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

namespace TooManyPeeps {

  class ContourFinder {

    private:
      std::vector<std::vector<cv::Point>> contours;
      std::vector<cv::Vec4i> hierarchy;
      std::vector<cv::Rect> boundingRectangles;

      double minimumArea;
      double maximumArea;

    public:
      ContourFinder(double minimumArea, double maximumArea);

    public:
      void find(const cv::Mat& frame);
      void draw(cv::Mat& frame);

    private:
      void filter(std::vector<std::vector<cv::Point>> * allContours, std::vector<cv::Vec4i> * allHierarchies);

  };

};
