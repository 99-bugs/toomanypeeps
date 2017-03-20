#include "contour_finder.h"

namespace TooManyPeeps {

  ContourFinder::ContourFinder(int minimumArea, int maximumArea) {
    this->minimumArea = minimumArea;
    this->maximumArea = maximumArea;
  }

  void ContourFinder::find(const cv::Mat& frame) {
    cv::Mat processFrame;
    frame.copyTo(processFrame);

    std::vector<std::vector<cv::Point>> allContours;
    std::vector<cv::Vec4i> allHierarchies;

    cv::findContours(processFrame, allContours, allHierarchies, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    filter(&allContours, &allHierarchies);

    std::cout << "Found contours: " << allContours.size() << " ";
  }

  void ContourFinder::filter(std::vector<std::vector<cv::Point>> * allContours,
    std::vector<cv::Vec4i> * allHierarchies) {

    contours.clear();
    hierarchy.clear();
    boundingRectangles.clear();

    // No actual filtering for the moment
    for (size_t i = 0; i < allContours->size(); i++) {
      contours.push_back((*allContours)[i]);
      hierarchy.push_back((*allHierarchies)[i]);
      boundingRectangles.push_back(cv::boundingRect(contours[i]));
    }
  }

  void ContourFinder::draw(cv::Mat& frame) {
    for( int idx = 0; idx >= 0; idx = hierarchy[idx][0] )
    {
        cv::Scalar color( rand()&255, rand()&255, rand()&255 );
        cv::drawContours(frame, contours, idx, color, cv::FILLED, 8, hierarchy);
    }

    for (size_t i = 0; i < boundingRectangles.size(); i++) {
      cv::Scalar color( rand()&255, rand()&255, rand()&255 );
      int thickness = 3;
      cv::rectangle(frame, boundingRectangles[i], color, thickness);
    }
  }

};
