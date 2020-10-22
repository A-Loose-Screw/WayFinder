#include "Drivetrain.h"
#include "path.h"
namespace wayfinder {
	class RobotControl : public Path {
	public:
		// Robot Config
		struct Config {
			wml::Drivetrain &drivetrain;
			double kp = 0,
			ki = 0, 
			kd = 0,
			gearBoxReduction = 0,
			wheelDiameter = 0,
			maxSpeed = 0,
			maxTurnSpeed = 0;
		};
	protected:
		void driveToTarget(sSpline spline, bool reverse, wml::Drivetrain &drivetrain);
	private:

		// PID/PathComplete Vals
		double _goal = 0;
		double _previousError = 0;
		double _sum = 0;
		bool pathComplete = false;
	};
};
