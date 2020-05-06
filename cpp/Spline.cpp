#include "Spline.h"

WayFinder::sPoint WayFinder::Spline::getSplinePoint(double t, std::vector<sPoint>points) {
  p1 = (int)t + 1;
  p2 = p1 + 1;
  p3 = p2 + 1;
  p0 = p1 - 1;

  t = t - (int)t;

  // sqrd/cubed t
  double tt = t * t;
  double ttt = tt * t;

  double q1 = -ttt + 2.0*tt - t;
  double q2 = 2.0*ttt - 5.0*tt + 2.0;
  double q3 = -3.0*ttt + 4.0*tt + t;
  double q4 = ttt - tt;

  double tx = 0.5*(points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
  double ty = 0.5*(points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

  return{tx, ty};
}

WayFinder::sPoint WayFinder::Spline::getSplineGradient(double t, std::vector<sPoint>points) {
  p1 = (int)t + 1;
  p2 = p1 + 1;
  p3 = p2 + 1;
  p0 = p1 - 1;

  t = t - (int)t;

  // sqrd/cubed t
  double tt = t * t;
  // double ttt = tt * t;

  double q1 = -3.0 * tt + 4.0*t - 1;
  double q2 = 9.0*tt - 10.0*t;
  double q3 = -9.0*tt + 8.0*t + 1.0;
  double q4 = 3.0*tt - 2.0*t;

  double tx = 0.5*(points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
  double ty = 0.5*(points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

  return{tx, ty};
}

double WayFinder::Spline::calcSegLength(int node, std::vector<sPoint>points) {
  double length = 0;
  double stepSize = 0.005; // make dynamic

  sPoint old_point, new_point;
  old_point = getSplinePoint((double)node, points);

  for (double t = 0; t < 1.0; t += stepSize) {
    new_point = getSplinePoint((double)node + t, points);
    double bufferLength = (new_point.x - old_point.x)*(new_point.x - old_point.x) + (new_point.y - old_point.y)*(new_point.y - old_point.y);
    length += sqrt(bufferLength);
  }

  return length;
}