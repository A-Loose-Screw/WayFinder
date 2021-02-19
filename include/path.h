#include <vector>
#include <math.h>
#include <iostream>
#include <string>

namespace wayfinder {
	class Path {
	public:
		struct sPoint {
			double x, y; // X & Y in meters

			// Positive length from waypoint. (Calculated by wayfinder. Manual input may affect robot)
			double segLength = 0;
			double totalLength = 0; // Length from start to this waypoint
		};

		struct sSpline {
			std::vector<sPoint> points;
			sPoint CtrlPt1, CtrlPt2;
			std::string name;
		};

		struct sPath {
			sSpline spline;
			double pathLength = 0; // In meters
			std::string name;
		};

		/**
		 * Get spline values. t represents position in spline. (meters)
		 */
		sPoint getSplinePoint(double t, sSpline spline);
		sPoint getSplineGradientPoints(double t, sSpline spline);
		double getSplineAngle_Rad(double t, sSpline spline);
		double getSplineAngle_Deg(double t, sSpline spline);
		double calculateSegLength(int node, sSpline spline);

		void setStepSize(double stepSize) { this->_stepSize = stepSize; }
		
	 private:
		double _stepSize = 0.005f;
	};
}