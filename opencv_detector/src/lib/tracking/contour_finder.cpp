#include "contour_finder.h"
#include "comparators/compare_contour_area.h"
#include "../helpers/color_generator.h"

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

    std::cout << "Found contours: " << allContours.size() << std::endl;
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

    // Sort by size
    if (indicesOfContoursTokeep.size() > 1) {
      std::sort(indicesOfContoursTokeep.begin(), indicesOfContoursTokeep.end(),
        CompareContourArea(areasOfContoursToKeep));
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

    use_mass_centers_as_reference();
    //use_bounding_rectangle_centers_as_reference();
  }

  void ContourFinder::use_bounding_rectangle_centers_as_reference(void) {
    // This is not correct yet. Still contains a bug
    throw "ContourFinder::use_bounding_rectangle_centers_as_reference contains a bug";
    objectReferencePoints.clear();
    for (size_t i = 0; i < boundingRectangles.size(); i++) {
      objectReferencePoints.push_back(cv::Point2f((boundingRectangles[i].x + boundingRectangles[i].width)/2,
      (boundingRectangles[i].y + boundingRectangles[i].height)/2));
    }
  }

  void ContourFinder::use_mass_centers_as_reference(void) {
      // Moments
      std::vector<cv::Moments> contourMoments(contours.size());
      for (size_t i = 0; i < contours.size(); i++) {
        contourMoments[i] = cv::moments(contours[i], false);
      }

      // Mass centers
      objectReferencePoints.clear();
      for (size_t i = 0; i < contours.size(); i++) {
        objectReferencePoints.push_back(cv::Point2f(contourMoments[i].m10/contourMoments[i].m00,
          contourMoments[i].m01/contourMoments[i].m00));
      }
  }

  void ContourFinder::draw(cv::Mat& frame, bool drawBoundingRectangles) {
    for(size_t i = 0; i < contours.size(); i++) {
      int thickness = 2;
      cv::drawContours(frame, contours, i, ColorGenerator::magenta(), thickness, 8, hierarchy);
    }

    if (drawBoundingRectangles) {
      for (size_t i = 0; i < boundingRectangles.size(); i++) {
        int thickness = 3;
        cv::rectangle(frame, boundingRectangles[i], ColorGenerator::magenta(), thickness);
      }
    }

    for (size_t i = 0; i < contours.size(); i++) {
      cv::circle(frame, objectReferencePoints[i], 4, ColorGenerator::magenta(), -1);
    }
  }

  std::vector<cv::Point2f> ContourFinder::get_object_reference_points(void) {
    return objectReferencePoints;
  }

};
