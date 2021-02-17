#include "WayFinder.h"

namespace wayfinder {
	WayFinder::WayFinder(Config &config) : _config(config) {
		std::cout << "Wayfinder buid successful" << std::endl;

		// @TODO Output config to console
	}

	// Approixmate length of spline & nodes
	Path::sPath WayFinder::buildPath(sSpline spline) {
		double totalPathLength = 0.0f;

		std::cout << "path building?" << std::endl;

		// Add the control points to the start and end of spline
		spline.points.insert(spline.points.begin(), spline.CtrlPt1);
		spline.points.push_back(spline.CtrlPt2);

		for (size_t i = 0; i < spline.points.size(); i++) {
			totalPathLength += (spline.points[i].segLength = calculateSegLength(i, spline));
			spline.points[i].totalLength = totalPathLength;
		}

		sPath path{spline, totalPathLength};
		return path;
	}

	bool WayFinder::followPath(sPath path, double dt, bool reverse) {
		return driveToTarget(path, reverse, dt, _config);
	}

	bool WayFinder::atWayPoint(int node, sPath path) {
		return getWayPoint(node, path, _config);
	}

	double WayFinder::getCurrentLocation(Config &config, bool inMeters) {
		return inMeters ? currentLocation_M(config) : currentLocation_R(config);
	}
}
