#pragma once
#include <vector>

namespace WayFinderSpline {
  struct sPoint {
    float x;
    float y;
  };

  struct sSpline {
    std::vector<sPoint> points;
    sPoint GetSplinePoint(float t);
  };

  class Spline {
   public:
    void PathCreator(sSpline spline);
  };
}