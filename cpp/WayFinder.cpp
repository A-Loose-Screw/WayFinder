#include "WayFinder.h"

void WayFinder::WayFinder::autoConfig(double kp, double ki, double kd, double gearboxReduction, double wheelDiameter, double maxSpeed, double maxTurnSpeed) {
  *_kp = kp;
  *_kd = kd;
  *_ki = ki;

  _gearboxReduction = gearboxReduction;
  _wheelDiameter = wheelDiameter;

  _maxSpeed = maxSpeed;
  _maxTurnSpeed = maxTurnSpeed;
}

