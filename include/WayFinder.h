#include "robotControl.h"

namespace wayfinder {
	class WayFinder : protected RobotControl {
	public:
		WayFinder(Config *config);
		~WayFinder();

		/**
		 * Build path (calculates spline and length of spline)
		 * Does this with multiple algorithms and loops
		 */
		sPath buildPath(sSpline spline);

		/**
		 * Uses drivetrain, deltatime, config and built path to drive to target
		 * Returns true once path complete
		 */
		bool followPath(sPath path, double dt, bool reverse = false);

		/**
		 * Returns true if robot is at waypoint number
		 */
		bool atWayPoint(int node, sPath path);
	private:
		Config *_config;
	};
}