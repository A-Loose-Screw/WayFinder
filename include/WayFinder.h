#include "robotControl.h"

namespace wayfinder {
	class WayFinder : protected RobotControl {
	public:
		WayFinder(Config &config);
		~WayFinder();

		/**
		 * Uses drivetrain & config along with given spline to drive to target
		 */
		void followPath(sSpline spline, bool reverse = false);

		/**
		 * Returns true if robot is at waypoint number
		 */
		bool atWayPoint(int wayPointIndex);
	private:
		Config &_config;
	};
};