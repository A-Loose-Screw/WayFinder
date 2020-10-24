#include "Drivetrain.h"
#include "path.h"
namespace wayfinder {
	class RobotControl : public Path {
	public:
		// Robot Config
		struct Config {
			wml::Drivetrain *drivetrain;
			double kp = 0,
			ki = 0, 
			kd = 0,
			gearBoxReduction = 0,
			wheelDiameter = 0, // In meters
			maxSpeed = 0,
			maxTurnSpeed = 0;
		};
	protected:
		bool driveToTarget(sPath path, bool reverse, double dt, Config *config);
	private:

		// Functions
		double rotationsToTarget(sPath path, Config *config); // returns length of target in rotations
		double internalPID(double dt, double goal, double input, Config *config); // PID for drivebase
		double currentLocation(Config *config); // Gets location average between encoders in meters or working encoder value in meters
		double gyroFollow(sPath path, double dt, Config *config); // follow gyro (returns power for drivebase)

		// PID/PathComplete Vals
		double _goal = 0;
		double _previousError = 0;
		double _sum = 0;
		bool _pathComplete = false;

		// Target Values (static)
		double _rotaionsToTarget = 0; // Rotation of wheel to target
		
		// Target Values (dynamic)
		double _currentLocationInMeters = 0;
	};
}
