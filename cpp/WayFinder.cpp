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

void WayFinder::WayFinder::followPath(lPath path, bool reversed) {
  followLinearPath(path, reversed);
} 

void WayFinder::WayFinder::followPath(sPath path, bool reversed) {
  followSplinePath(path, reversed);
}