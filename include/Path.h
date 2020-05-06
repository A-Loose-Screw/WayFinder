#pragma once
#include <iostream>
#include <math>
#include <vector>

// path types
#include "Spline.h"
// #include ""

namespace WayFinder {
  class Path : public Spline {
    Path();
    ~Path() {
      printf("Path Object Deconstructed");
    }

    public:

  }
}