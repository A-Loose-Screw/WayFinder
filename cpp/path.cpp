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

	Path::sPoint Path::getSplineGradientPoints(double t, sSpline spline) {
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

		return { tx, ty };
	}

	double Path::getSplineAngle_Rad(double t, sSpline spline) {
		sPoint gradient = getSplineGradientPoints(t, spline);
		return atan2(gradient.y, gradient.x);
	}

	double Path::getSplineAngle_Deg(double t, sSpline spline) {
		return (getSplineAngle_Rad(t, spline) * (180/M_PI));
	}

	// Calculate seg length needs to happen once. (in loop. will slow robot down)
	// Calculation is approximation (There is no answer to life... except 42)
	double Path::calculateSegLength(int node, sSpline spline) {
		double length = 0.0f;
		double stepSize = _stepSize;

		sPoint old_point, new_point;
		old_point = getSplinePoint((double)node, spline);

		for (double t = 0; t < 1.0f; t += stepSize) {
			new_point = getSplinePoint((double)node + t, spline);

			// Calc length (pythag)
			double bufferLength = (new_point.x - old_point.x)*(new_point.x - old_point.x) + (new_point.y - old_point.y)*(new_point.y - old_point.y);
			length += sqrt(bufferLength);

			old_point = new_point;

			std::cout << "Length Continuum: " << length << std::endl;
		}

		std::cout << "Final Length: " << length << std::endl;

		return length;
	}
}