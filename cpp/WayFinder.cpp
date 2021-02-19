#include "WayFinder.h"

namespace wayfinder {
	WayFinder::WayFinder(Config &config) : _config(config) {

		// @TODO Output config to console
		std::cout << "*** WayFinder Config ***" << std::endl;

		std::cout << "Left Encoder Invert: " << _config.invertLeftENC << std::endl;
		std::cout << "Right Encoder Invert: " << _config.invertRightENC << std::endl;

		std::cout << "PID Drive: " << _config.kp_drive << ", " << _config.ki_drive << ", " << _config.kd_drive << std::endl;
		std::cout << "PID Turn: " << _config.kp_turn << ", " << _config.ki_turn << ", " << _config.kd_turn << std::endl;

		std::cout << "Reduction " << _config.gearBoxReduction << ":1" << std::endl;
		std::cout << "Max Speed: " << _config.maxSpeed << std::endl;
		std::cout << "Max Turn Speed: " << _config.maxTurnSpeed << std::endl;
	}

	// Approixmate length of spline & nodes
	Path::sPath WayFinder::buildPath(sSpline spline) {
		double totalPathLength = 0.0f;

		std::cout << "\n** " << spline.name << " " << "Path Building **" << std::endl;

		// Add the control points to the start and end of spline
		spline.points.insert(spline.points.begin(), spline.CtrlPt1);
		spline.points.push_back(spline.CtrlPt2);

		for (size_t i = 0; i < spline.points.size(); i++) {
			totalPathLength += (spline.points[i].segLength = calculateSegLength(i, spline));
			spline.points[i].totalLength = totalPathLength;
		}

		std::cout << "CtrlPt1: " << spline.points[0].x << "," << spline.points[0].y << std::endl;
		std::cout << "CtrlPt2: " << spline.points[3].x << "," << spline.points[3].y << std::endl;


		sPath path{spline, totalPathLength, spline.name};
		std::cout << "Total Length: " << path.pathLength << std::endl;
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