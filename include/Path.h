#pragma once

// path types
#include "Spline.h"
#include "Linear.h"

namespace WayFinder {
  class Path : public Spline, public Linear {
   public:
    Path();
    ~Path() {
      printf("Path Object Deconstructed");
    }

    // Path types
    std::vector<sPoint> sPath;
    std::vector<lPoint> lPath;

    void followPath(std::vector<lPoint> path, bool reversed);
    void followPath(std::vector<sPoint> path, bool reversed);

   private:
  };
}