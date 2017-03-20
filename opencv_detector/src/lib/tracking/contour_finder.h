#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

namespace TooManyPeeps {

  class ContourFinder {

    private:
      std::vector<std::vector<cv::Point>> contours;
      std::vector<cv::Vec4i> hierarchy;
      std::vector<cv::Rect> boundingRectangles;
      std::vector<cv::Point2f> objectReferencePoints;

      double minimumArea;
      double maximumArea;

    public:
      ContourFinder(double minimumArea, double maximumArea);

    public:
      void find(const cv::Mat& frame);
      void draw(cv::Mat& frame);

    public:
      std::vector<cv::Point2f> get_object_reference_points(void);

    private:
      void filter(std::vector<std::vector<cv::Point>> * allContours, std::vector<cv::Vec4i> * allHierarchies);
      void use_mass_centers_as_reference(void);
      void use_bounding_rectangle_centers_as_reference(void);
  };

};
