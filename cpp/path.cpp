#include "path.h"
namespace wayfinder {
	Path::sPoint Path::getSplinePoint(double t, sSpline spline) {
		int p0, p1, p2, p3;

		p1 = (int)t + 1;
		p2 = p1 + 1;
		p3 = p2 + 1;
		p0 = p1 - 1;

		t = t - (int)t;

		double tt = t * t;
		double ttt = tt * t;

		double q1 = -ttt + 2.0f*tt - t;
		double q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
		double q3 = -3.0f*ttt + 4.0f*tt + t;
		double q4 = ttt - tt;

		double tx = 0.5f * (spline.points[p0].x * q1 + spline.points[p1].x * q2 + spline.points[p2].x * q3 + spline.points[p3].x * q4);
		double ty = 0.5f * (spline.points[p0].y * q1 + spline.points[p1].y * q2 + spline.points[p2].y * q3 + spline.points[p3].y * q4);

		return{ tx, ty };
	}

	Path::sPoint Path::getSplineGradient(double t, sSpline spline) {
		int p0, p1, p2, p3;
		p1 = (int)t + 1;
		p2 = p1 + 1;
		p3 = p2 + 1;
		p0 = p1 - 1;

		t = t - (int)t;

		double tt = t * t;
		// double ttt = tt * t;

		double q1 = -3.0f * tt + 4.0f*t - 1;
		double q2 = 9.0f*tt - 10.0f*t;
		double q3 = -9.0f*tt + 8.0f*t + 1.0f;
		double q4 = 3.0f*tt - 2.0f*t;

		double tx = 0.5f * (spline.points[p0].x * q1 + spline.points[p1].x * q2 + spline.points[p2].x * q3 + spline.points[p3].x * q4);
		double ty = 0.5f * (spline.points[p0].y * q1 + spline.points[p1].y * q2 + spline.points[p2].y * q3 + spline.points[p3].y * q4);

		return{ tx, ty };
	}
}