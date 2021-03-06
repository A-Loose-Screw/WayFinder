#include "Drivetrain.h"
#include "path.h"
#include "NTProvider.h"

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
			double *kp_drive,
			*ki_drive,
			*kd_drive,

			*kp_turn,
			*ki_turn,
			*kd_turn,

			gearBoxReduction = 0,
			wheelDiameter = 0, // In meters
			maxSpeed = 0,
			maxTurnSpeed = 0;
		};

		/**
		 * Lowers the bar of when the path should be completed. 
		 * E.g path length is 30 wheel rotations, & bar set to 0.5
		 * the path will return complete when the robot reaches 29.5 wheel rotations and over
		 * Set higher for robots which tend to have more encoder drift
		 */
		void setBarStop(double bar) {_bar = bar;}

		/**
		 * Returns wheel rotations to target
		 */
		double getRotationsToTarget(sPath path, Config &config, bool wheelRotations = false) {
			return rotationsToTarget(path, config, wheelRotations);
		}

		/**
		 * Test PID driving for 2 meters or by parameter set
		 */
		void testDrivePID(double dt, Config &config, double meters2drive = 2);

		/**
		 * turns 90 degrees or by parameter set
		 */
		void testTurnPID(double dt, Config &config, double angle2turn = 90);

		/**
		 * Test full PID to length and turn
		 */
		void testPID(double dt, Config &config, double meters2drive = 2, double angle2turn = 90);


		/**
		 * Get current locations
		 */
		double getCurrentLocation(Config &config, bool meters = false, bool wheelRotations = true);
		
	protected:

		bool driveToTarget(sPath path, bool reverse, double dt, Config &config);
		bool getWayPoint(int node, sPath path, Config &config);
		double currentLocation_M(Config &config); // Gets location average between encoders in meters or working encoder value in meters
		double currentLocation_R(Config &config, bool wheelRotations = false); // Gets location average between encoders in rotations or working encoder value in rotations

	private:
		// Functions
		double rotationsToTarget(sPath path, Config &config, bool wheelRotations); // returns length of target in rotations
		double internalPID(double dt, double goal, double input, Config &config, bool turnLoop = false); // PID for drivebase
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
