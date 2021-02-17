#include "Drivetrain.h"
#include "path.h"
namespace wayfinder {
	class RobotControl : public Path {
	public:
		// Robot Config
		struct Config {

			// Drivetrain
			wml::Drivetrain *drivetrain;
			bool invertLeftENC = false;
			bool invertRightENC = false;

			// Characterise Vals
			double kp = 0,
			ki = 0,
			kd = 0,
			gearBoxReduction = 0,
			wheelDiameter = 0, // In meters
			maxSpeed = 0,
			maxTurnSpeed = 0;
		};

		/**
		 * Lowers the bar of when the path should be completed. 
		 * E.g path length is 30 rotations, & bar set to 0.5
		 * the path will return complete when the robot reaches 29.5 rotations and over
		 * Set higher for robots which tend to have more encoder drift
		 */
		void setBarStop(double bar) {_bar = bar;}

		double getRotationsToTarget_STATIC(sPath path, Config &config) {
			return rotationsToTarget(path, config);
		}
	protected:

		bool driveToTarget(sPath path, bool reverse, double dt, Config &config);
		bool getWayPoint(int node, sPath path, Config &config);
		double currentLocation_M(Config &config); // Gets location average between encoders in meters or working encoder value in meters
		double currentLocation_R(Config &config); // Gets location average between encoders in rotations or working encoder value in rotations

	private:

		// Functions
		double rotationsToTarget(sPath path, Config &config); // returns length of target in rotations
		double internalPID(double dt, double goal, double input, Config &config); // PID for drivebase
		double gyroFollow(sPath path, double dt, Config &config); // follow gyro (returns power for drivebase)


		// PID/PathComplete Vals
		double _goal = 0;
		double _previousError = 0;
		double _sum = 0;
		bool _pathComplete = false;

		// Target Values (static)
		double _rotationsToTarget = 0; // Rotation of wheel to target
		double _bar = 0;
	};
}
