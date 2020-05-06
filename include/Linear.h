#pragma once
#include <iostream>
#include <cmath>
#include <vector>

namespace WayFinder {
  struct lPoint {
    double x, y, length = 0;
  };

  class Linear {
   public:
    Linear();
    ~Linear() {
      printf("Linear Object Decontructed");
    }
   private:

  };
}