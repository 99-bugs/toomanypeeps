#include "contour_finder.h"

namespace TooManyPeeps {

  ContourFinder::ContourFinder(double minimumArea, double maximumArea) {
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

    std::vector<size_t> indicesOfContoursTokeep;
    std::vector<double> areasOfContoursToKeep;

    for (size_t i = 0; i < allContours->size(); i++) {
      double area = cv::contourArea(cv::Mat((*allContours)[i]));
      std::cout << "Area [" << i << "] = " << area;
      if (area <= maximumArea && area >= minimumArea) {
        std::cout << " <= kept" << std::endl;
        indicesOfContoursTokeep.push_back(i);
        areasOfContoursToKeep.push_back(area);
      } else {
          std::cout << " <= ditched" << std::endl;
      }
    }

    contours.clear();
    hierarchy.clear();
    boundingRectangles.clear();

    // No actual filtering for the moment
    for (size_t i = 0; i < indicesOfContoursTokeep.size(); i++) {
      contours.push_back((*allContours)[indicesOfContoursTokeep[i]]);
      hierarchy.push_back((*allHierarchies)[indicesOfContoursTokeep[i]]);
      boundingRectangles.push_back(cv::boundingRect(contours[i]));
    }
  }

  void ContourFinder::draw(cv::Mat& frame) {
    for(size_t i = 0; i < contours.size(); i++)
    {
        cv::Scalar color( rand()&255, rand()&255, rand()&255 );
        cv::drawContours(frame, contours, i, color, cv::FILLED, 8, hierarchy);
    }

    for (size_t i = 0; i < boundingRectangles.size(); i++) {
      cv::Scalar color( rand()&255, rand()&255, rand()&255 );
      int thickness = 3;
      cv::rectangle(frame, boundingRectangles[i], color, thickness);
    }
  }

};
