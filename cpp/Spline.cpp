#include "Spline.h"

void WayFinderSpline::Spline::PathCreator(sSpline path) {
  for (size_t i = 0; i < path.points.size(); i++) {
    
  }
}

WayFinderSpline::sPoint WayFinderSpline::sSpline::GetSplinePoint(float t) {
  int p0, p1, p2, p3;
  p1 = (int)t + 1;
  p2 = p1 + 1;
  p3 = p2 + 1;
  p0 = p1 - 1;

  float tt = t * t;
  float ttt = tt * t;

  // field of influence 
  float q1 = -ttt + 2.0f * tt - t;
  float q2 = 3.0f * ttt - 5.0f * tt + 2.0f;
  float q3 = -3.0f * ttt + 4.0f*tt + t;
  float q4 = ttt - tt;

  float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
  float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

  return {tx, ty};
}