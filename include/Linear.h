#pragma once
#include <iostream>
#include <cmath>
#include <vector>

namespace wayFinder {
  struct lPoint {
    double x, y, length = 0;
  };

  class Linear {
    Linear();
    ~Linear() {
      printf("Linear Object Decontructed");
    }
   private:

  }
}