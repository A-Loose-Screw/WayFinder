#pragma once

#ifdef USING_WML
  #include "Drivetrain.h"
#endif

namespace WayFinder {
  class RobotControl {
   public:
    #ifdef USING_WML
    RobotControl(wml::Drivetrain &drivetrain);
    #endif
   protected:

   private:
    double turnToTarget();
    double rotationsToTarget();
    void driveToTarget();
  };
}