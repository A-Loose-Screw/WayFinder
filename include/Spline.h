#pragma once
#include <iostream>
#include <cmath>
#include <vector>

namespace WayFinder {
  struct sPoint {
    double x, y, length = 0;
  };

  class Spline {
   protected:

    // Spline Calulators
    sPoint getSplinePoint(double t, std::vector<sPoint>points);
    sPoint getSplineGradient(double t, std::vector<sPoint>points);
    double calcSegLength(int node, std::vector<sPoint>points);


    // Influencers
    int p0, p1, p2, p3;
  };
}