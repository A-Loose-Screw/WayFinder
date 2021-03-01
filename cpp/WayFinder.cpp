#include "WayFinder.h"

namespace wayfinder {
	WayFinder::WayFinder(Config &config) : _config(config) {

		// @TODO Output config to console
		std::cout << "*** WayFinder Config ***" << std::endl;

		std::cout << "Left Encoder Invert: " << _config.invertLeftENC << std::endl;
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Left ENC Invert").SetBoolean(_config.invertLeftENC);

		std::cout << "Right Encoder Invert: " << _config.invertRightENC << std::endl;
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Right ENC Invert").SetBoolean(_config.invertRightENC);

		std::cout << "PID Drive: " << _config.kp_drive << ", " << _config.ki_drive << ", " << _config.kd_drive << std::endl;
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Drive_P").SetDouble(*_config.kp_drive);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Drive_I").SetDouble(*_config.ki_drive);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Drive_D").SetDouble(*_config.kd_drive);

		std::cout << "PID Turn: " << _config.kp_turn << ", " << _config.ki_turn << ", " << _config.kd_turn << std::endl;
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Turn_P").SetDouble(*_config.kp_turn);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Turn_I").SetDouble(*_config.ki_turn);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Turn_D").SetDouble(*_config.kd_turn);

		std::cout << "Reduction " << _config.gearBoxReduction << ":1" << std::endl;
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Gear Reduction").SetDouble(_config.gearBoxReduction);

		std::cout << "Max Speed: " << _config.maxSpeed << std::endl;
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Max Drive Speed").SetDouble(_config.maxSpeed);

		std::cout << "Max Turn Speed: " << _config.maxTurnSpeed << std::endl;
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Max Turn Speed").SetDouble(_config.maxTurnSpeed);
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

			std::string pointX = "Point " + std::to_string(i) + " X";
			std::string pointY = "Point " + std::to_string(i) + " Y";

			nt::NetworkTableInstance::GetDefault().GetTable("WayFinderPaths")->GetSubTable(spline.name)->GetEntry(pointX).SetDouble(spline.points[i].x);
			nt::NetworkTableInstance::GetDefault().GetTable("WayFinderPaths")->GetSubTable(spline.name)->GetEntry(pointY).SetDouble(spline.points[i].y);
		}

		std::cout << "CtrlPt1: " << spline.CtrlPt1.x << "," << spline.CtrlPt1.y << std::endl;
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinderPaths")->GetSubTable(spline.name)->GetEntry("Control Point 1 X").SetDouble(spline.CtrlPt1.x);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinderPaths")->GetSubTable(spline.name)->GetEntry("Control Point 1 Y").SetDouble(spline.CtrlPt1.y);

		std::cout << "CtrlPt2: " << spline.CtrlPt2.x << "," << spline.CtrlPt2.y << std::endl;
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinderPaths")->GetSubTable(spline.name)->GetEntry("Control Point 2 X").SetDouble(spline.CtrlPt2.x);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinderPaths")->GetSubTable(spline.name)->GetEntry("Control Point 2 Y").SetDouble(spline.CtrlPt2.y);


		sPath path{spline, totalPathLength, spline.name};
		std::cout << "Total Length: " << path.pathLength << std::endl;

		nt::NetworkTableInstance::GetDefault().GetTable("WayFinderPaths")->GetSubTable(spline.name)->GetEntry("Total Path Length").SetDouble(path.pathLength);

		return path;
	}

	bool WayFinder::followPath(sPath path, double dt, bool reverse) {
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinderFollower")->GetSubTable(path.name)->GetEntry("Following Path").SetBoolean(true);
		return driveToTarget(path, reverse, dt, _config);
	}

	bool WayFinder::atWayPoint(int node, sPath path) {
		return getWayPoint(node, path, _config);
	}

	double WayFinder::getCurrentLocation(Config &config, bool inMeters) {
		double location = inMeters ? currentLocation_M(config) : currentLocation_R(config);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinderFollower")->GetEntry("Current Location").SetDouble(location);
		return location;
	}
}