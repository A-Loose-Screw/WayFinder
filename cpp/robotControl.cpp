#include "robotControl.h"

namespace wayfinder {
	double RobotControl::rotationsToTarget(sPath path, Config *config) {
		double distanceCM = path.pathLength*100;
		return (config->gearBoxReduction * (distanceCM/(M_PI * config->wheelDiameter)));
	}

	double RobotControl::internalPID(double dt, double goal, double input, Config *config) {
		double error = goal - input;
		double derror = (error - _previousError)/dt;

		_sum = _sum + error * dt;

		double output = config->kp * error + config->ki * _sum + config->kd * derror;
		
		// Just in case the PID is a bit wack. (make sure value is between -1 and 1)
		output = output < -1 ? -1 : output; // Smaller than 1
		output = output > 1 ? 1 : output; // Bigger than 1
		return output;
	}

	double inverse(double input) {
		return input < 0 ? abs(input) : -input;
	}

	double RobotControl::currentLocation_R(Config *config) {
		double currentRotationsLeft = config->drivetrain->GetConfig().leftDrive.encoder->GetEncoderRotations();
		double currentRotationsRight = config->drivetrain->GetConfig().rightDrive.encoder->GetEncoderRotations();

		if (currentRotationsLeft != 0 || currentRotationsRight != 0) {
			return ((currentRotationsLeft + currentRotationsRight)/2); // If both encoders are detected (not 0) use average
		} else {
			return abs(currentRotationsLeft) > abs(currentRotationsRight) ? currentRotationsLeft : currentRotationsRight; // else use whichever encoder has a value or has a bigger value than the other (encoder might disconnect during match)
		}
	}

	double RobotControl::currentLocation_M(Config *config) {
		double currentRotationsLeft = config->drivetrain->GetConfig().leftDrive.encoder->GetEncoderRotations();
		double currentRotationsRight = config->drivetrain->GetConfig().rightDrive.encoder->GetEncoderRotations();

		double currentMetersLeft = currentRotationsLeft * (M_PI * config->wheelDiameter);
		double currentMetersRight = currentRotationsRight * (M_PI * config->wheelDiameter);

		if (currentRotationsLeft != 0 || currentRotationsRight != 0) {
			return ((currentMetersLeft + currentMetersRight)/2); // If both encoders are detected (not 0) use average
		} else {
			return abs(currentMetersLeft) > abs(currentMetersRight) ? currentMetersLeft : currentMetersRight; // else use whichever encoder has a value or has a bigger value than the other (encoder might disconnect during match)
		}
	}

	double RobotControl::gyroFollow(sPath path, double dt, Config *config) {
		double gyroGoal = getSplineAngle_Deg(currentLocation_R(config), path.spline);
		double output = internalPID(dt, gyroGoal, config->drivetrain->GetConfig().gyro->GetAngle(), config);
		output *= config->maxTurnSpeed; // Limit turn speed. (Just in case it's a bit too jittery)
		return output;
	}

	bool RobotControl::driveToTarget(sPath path, bool reverse, double dt, Config *config) {
		_rotationsToTarget = rotationsToTarget(path, config);

		// Check if at target
		if ((currentLocation_R(config)-_bar) >= _rotationsToTarget) {
			return true;
		} else {

			double leftSpeed = internalPID(dt, _rotationsToTarget, config->drivetrain->GetConfig().leftDrive.encoder->GetEncoderRotations(), config);
			double rightSpeed = internalPID(dt, _rotationsToTarget, config->drivetrain->GetConfig().rightDrive.encoder->GetEncoderRotations(), config);

			// gyro follow
			leftSpeed += gyroFollow(path, dt, config);
			rightSpeed -= gyroFollow(path, dt, config);

			// Limit power based on max speed (-1 to 1)
			leftSpeed *= config->maxSpeed;
			rightSpeed *= config->maxSpeed;

			// Inverse the values if reverse is true
			leftSpeed = reverse ? inverse(leftSpeed) : leftSpeed;
			rightSpeed = reverse ? inverse(rightSpeed) : rightSpeed;

			// Set Drivetrain
			config->drivetrain->Set(leftSpeed, rightSpeed); // Set Drivetrain
		
			return false;
		}

	}

	bool RobotControl::getWayPoint(int node, sPath path, Config *config) {
		double nodePointLength = path.spline.points[node].totalLength;
		if ((currentLocation_R(config)-_bar) >= nodePointLength) {
			return true;
		} else {
			return false;
		}
	}
}