#include <vector>

namespace wayfinder {
	class Path {
	public:
		struct sPoint {
			double x, y; // X & Y in meters
		};

		struct sSpline {
			std::vector<sPoint> points;
			sPoint CtrlPt1 = points.front(), CtrlPt2 = points.back();
		};
		sPoint getSplinePoint(double t, sSpline spline);
		sPoint getSplineGradient(double t, sSpline spline);
	};
};