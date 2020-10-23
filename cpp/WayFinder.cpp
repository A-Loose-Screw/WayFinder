#include "WayFinder.h"

namespace wayfinder {
	WayFinder::WayFinder(Config *config) {
		_config = config;
	}

	// Approixmate length of spline
	Path::sPath WayFinder::buildPath(sSpline spline) {
		double totalPathLength = 0.0f;
		for (size_t i = 0; i < spline.points.size(); i++) {
			totalPathLength += (spline.points[i].segLength = calculateSegLength(i, spline));
		}

		sPath path{spline, totalPathLength};
		return path;
	}

	bool WayFinder::followPath(sPath path, double dt, bool reverse) {
		return driveToTarget(path, reverse, dt, _config);
	}

	bool WayFinder::atWayPoint(int node) {
		return false;
	}
}
