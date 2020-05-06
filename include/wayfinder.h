#pragma once
#include "Path.h"

#ifdef USING_WML
 #include "Drivetrain.h"
#endif

namespace WayFinder {
  class WayFinder : public Path {
   public:
   #ifdef USING_WML
    WayFinder();
   #else
    WayFinder();
   #endif
    ~WayFinder();

   void config();

   private:

    // PID Values
    double *_kp;
    double *_kd;
    double *_ki;

    double _gearBoxReduction;
    double _wheelDiameter;
  };
}