#include "robotControl.h"

namespace wayfinder {
	double RobotControl::rotationsToTarget(sPath path, Config &config, bool wheelRotations) {

		if (wheelRotations) {
			return (path.pathLength/(M_PI * config.wheelDiameter));
		} else {
			return (config.gearBoxReduction * (path.pathLength/(M_PI * config.wheelDiameter)));
		}
	}

	double RobotControl::internalPID(double dt, double goal, double input, Config &config, bool turnLoop) {
		double error = goal - input;
		double derror = (error - _previousError)/dt;

		_sum = _sum + error * dt;

		double output = 0;

		if (turnLoop) {
			output = *config.kp_turn * error + *config.ki_turn * _sum + *config.kd_turn * derror;
		} else {
			output = *config.kp_drive * error + *config.ki_drive * _sum + *config.kd_drive * derror;
		}
		
		// Just in case the PID is a bit wack. (make sure value is between -1 and 1)
		output = std::max(output, -1.0);
		output = std::min(output, 1.0);

		return output;
	}

	void RobotControl::testDrivePID(double dt, Config &config, double meters2drive) {
		double goalRotations = (meters2drive/(M_PI * config.wheelDiameter));
		double leftSpeed = internalPID(dt, goalRotations, currentLocation_R(config, true), config, false);
		double rightSpeed = internalPID(dt, goalRotations, currentLocation_R(config, true), config, false);
		
		leftSpeed *= config.maxSpeed;
		rightSpeed *= config.maxSpeed;

		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetEntry("leftSpeed").SetDouble(leftSpeed);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetEntry("rightSpeed").SetDouble(rightSpeed);

		config.drivetrain->Set(leftSpeed, rightSpeed);
	}

	void RobotControl::testTurnPID(double dt, Config &config, double angle2turn) {
		double angleSpeed = internalPID(dt, angle2turn, config.drivetrain->GetConfig().gyro->GetAngle(), config, true);
		double leftSpeed = 0, rightSpeed = 0;
		
		angleSpeed *= config.maxTurnSpeed;
		leftSpeed += angleSpeed;
		rightSpeed -= angleSpeed;

		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetEntry("angleSpeed").SetDouble(angleSpeed);

		config.drivetrain->Set(leftSpeed, rightSpeed);
	}

	double inverse(double input) {
		return -input;
	}

	void RobotControl::testPID(double dt, Config &config, double meters2drive, double angle2turn) {
		double goalRotations = (meters2drive/(M_PI * config.wheelDiameter));
		double angleSpeed = internalPID(dt, angle2turn, config.drivetrain->GetConfig().gyro->GetAngle(), config, false);

		angleSpeed *= config.maxTurnSpeed;

		double leftSpeed = internalPID(dt, goalRotations, currentLocation_R(config, true), config, false);
		double rightSpeed = internalPID(dt, goalRotations, currentLocation_R(config, true), config, false);
		
		leftSpeed += angleSpeed;
		rightSpeed -= angleSpeed;

		leftSpeed *= config.maxSpeed;
		rightSpeed *= config.maxSpeed;

		// Networking
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetEntry("leftSpeed").SetDouble(leftSpeed);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetEntry("rightSpeed").SetDouble(rightSpeed);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetEntry("angleSpeed").SetDouble(angleSpeed);


		config.drivetrain->Set(leftSpeed, rightSpeed);
	}

	double RobotControl::getCurrentLocation(Config &config, bool meters, bool wheelRotations) {
		if (meters) {
			return currentLocation_M(config);
		} else {
			return currentLocation_R(config, wheelRotations);
		}
	}


	double RobotControl::currentLocation_R(Config &config, bool wheelRotations) { // Location in wheel rotations (not motor rotations)

		double currentRotationsLeft = config.invertLeftENC == true ? inverse(config.drivetrain->GetConfig().leftDrive.encoder->GetEncoderRotations()) : config.drivetrain->GetConfig().leftDrive.encoder->GetEncoderRotations();
		double currentRotationsRight = config.invertRightENC == true ? inverse(config.drivetrain->GetConfig().rightDrive.encoder->GetEncoderRotations()) : config.drivetrain->GetConfig().rightDrive.encoder->GetEncoderRotations();

		if (wheelRotations) {
			currentRotationsLeft /= config.gearBoxReduction;
			currentRotationsRight /= config.gearBoxReduction;
		}

		if (currentRotationsLeft != 0 || currentRotationsRight != 0) {
			return ((currentRotationsLeft + currentRotationsRight)/2); // If both encoders are detected (not 0) use average
		} else {
			return fabs(currentRotationsLeft) > fabs(currentRotationsRight) ? currentRotationsLeft : currentRotationsRight; // else use whichever encoder has a value or has a bigger value than the other (encoder might disconnect during match)
		}
	}

	double RobotControl::currentLocation_M(Config &config) {

		double currentRotationsLeft = config.invertLeftENC ? inverse(config.drivetrain->GetConfig().leftDrive.encoder->GetEncoderRotations()) : config.drivetrain->GetConfig().leftDrive.encoder->GetEncoderRotations();
		double currentRotationsRight = config.invertRightENC ? inverse(config.drivetrain->GetConfig().rightDrive.encoder->GetEncoderRotations()) : config.drivetrain->GetConfig().rightDrive.encoder->GetEncoderRotations();

		currentRotationsLeft /= config.gearBoxReduction;
		currentRotationsRight /= config.gearBoxReduction;

		double currentMetersLeft = currentRotationsLeft * (M_PI * config.wheelDiameter);
		double currentMetersRight = currentRotationsRight * (M_PI * config.wheelDiameter);

		if (currentRotationsLeft != 0 || currentRotationsRight != 0) {
			return ((currentMetersLeft + currentMetersRight)/2); // If both encoders are detected (not 0) use average
		} else {
			return fabs(currentMetersLeft) > fabs(currentMetersRight) ? currentMetersLeft : currentMetersRight; // else use whichever encoder has a value or has a bigger value than the other (encoder might disconnect during match)
		}
	}

	double RobotControl::gyroFollow(sPath path, double dt, Config &config) {
		double gyroGoal = getSplineAngle_Deg(currentLocation_M(config), path.spline);
		double output = internalPID(dt, gyroGoal, config.drivetrain->GetConfig().gyro->GetAngle(), config, true);
		output *= config.maxTurnSpeed; // Limit turn speed. (Just in case it's a bit too jittery)
		return output;
	}

	bool RobotControl::driveToTarget(sPath path, bool reverse, double dt, Config &config) {
		_rotationsToTarget = rotationsToTarget(path, config, true);

		// Check if at target
		if ((currentLocation_R(config, true)-_bar) >= _rotationsToTarget) {
			config.drivetrain->Set(0,0);
			return true;
		} else {
			
			// PID left right speeds
			double leftSpeed = internalPID(dt, _rotationsToTarget, currentLocation_R(config), config, false);
			double rightSpeed = internalPID(dt, _rotationsToTarget, currentLocation_R(config), config, false);
			double turnSpeed = gyroFollow(path, dt, config);

			// gyro follow
			leftSpeed += turnSpeed;
			rightSpeed -= turnSpeed;

			// If reversed
			leftSpeed = reverse ? inverse(leftSpeed) : leftSpeed;
			rightSpeed = reverse ? inverse(rightSpeed) : rightSpeed;

			// Limit power based on max speed (-1 to 1)
			leftSpeed *= config.maxSpeed;
			rightSpeed *= config.maxSpeed;

			// Network Tables
			nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetEntry("leftSpeed").SetDouble(leftSpeed);
			nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetEntry("rightSpeed").SetDouble(rightSpeed);
			nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetEntry("angleSpeed").SetDouble(turnSpeed);

			// Set Drivetrain
			config.drivetrain->Set(leftSpeed, rightSpeed); // Set Drivetrain
		
			return false;
		}
	}

	bool RobotControl::getWayPoint(int node, sPath path, Config &config) {
		double nodePointLength = path.spline.points[node].totalLength;
		if ((currentLocation_M(config)-_bar) >= nodePointLength) {
			return true;
		} else {
			return false;
		}
	}
}