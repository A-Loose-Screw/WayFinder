#pragma once

// path types
#include "Spline.h"
#include "Linear.h"

namespace WayFinder {
  class Path : public Spline, public Linear {
   public:
    // Path type define
    struct lPath {
      std::vector<lPoint> points;
    };
    struct sPath {
      std::vector<sPoint> points;
    };

    void followLinearPath(lPath path, bool reversed);
    void followSplinePath(sPath path, bool reversed);

   private:
    Spline _spline;
    Linear _linear;
  };
}