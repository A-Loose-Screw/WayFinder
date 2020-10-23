#pragma once

#include "Drivetrain.h"
#include "Spline.h"

class WayFinder {
  public:

    struct Waypoint {
      double p1x, p1y, startAngle;
      double p2x, p2y, endAngle;
      bool reverse;
    };

    /**
     * Way Finder. The crappy version of pathfinder. BUT WITH NO CURVE TRAJECTORIES. because, it's week 6.
     * and i'm not in the mood to build that. Initialize by inputing your PID values & drivetrain along 
     * with your gearbox reduction & wheel diameter. note gearbox reduction is from motor to output rotations on the wheel (12:1). 
     */
    WayFinder(double kp, double ki, double kd, wml::Drivetrain &drivetrain, double gearboxReduction, double WheelDiameter);

    /**
     * Configure the speeds and values of your auto (Defult is 0.5 & 0.4)
     */
    void Config(double MaxSpeed, double MaxTurnSpeed);

    /**
     * Using pathweaver or whatever you choose to calculate your waypoints, input the coords
     * (in meters) of your desired locations, your start x & y, and your ending x & y.
     * Also your desired starting angle (Usually zero) and your ending angle in degrees.  
     * Also choose to reverse drivetrain or not (Drive backwards)
     */
    void GotoWaypoint(double wypt1x, double wypt1y, double startAngle, double wypt2x, double wypt2y, double endAngle, bool reverse, double dt);

    /**
     * Using pathweaver or whatever you choose to calculate your waypoints, input the coords
     * (in meters) of your desired locations, your start x & y, and your ending x & y.
     * Also your desired starting angle (Usually zero) and your ending angle in degrees.  
     * Also choose to reverse drivetrain or not (Drive backwards)
     */
    void GotoWaypoint(Waypoint wp, double dt) {
      GotoWaypoint(wp.p1x, wp.p1y, wp.startAngle, wp.p2x, wp.p2y, wp.endAngle, wp.reverse, dt);
    }

    /** 
     * Test Your Driving PID 
     * (if it gets to the desired goal with reasonable acuracy then the PID shouldn't need changing)
     */
    void TestPID(double dt, double goal);


    /**
     * Gets the static distance of the goal in rotations
     */
    double GetDistanceInRotations();


    /**
     * Gets the average location between the left and riht encoders
     * to grab the location of the drivetrain
     */
    double GetDrivetrainCurrentLocation();


    /**
     * Gets if the waypoint is complete, 
     * Returns a true or false value
     */ 
    bool GetWaypointComplete();



  private:
    void LeftDriveToTarget(double dt, double goal);
    void RightDriveToTarget(double dt, double goal);
    void DriveToTarget(double dt, double goal, bool reverse);
    void TurnToTarget(double dt, double input, double goal, bool reverse);

    double RotationsToTarget(double p1x, double p1y, double p2x, double p2y);
    double InternalPID(double dt, double goal, double input);
    double InverseNumber(double input);
    void EndCase();
    void EndTurn();
    void EndCheckPoint();
    void StartWaypoint();

    // Drivetrain
    wml::Drivetrain &_drivetrain;
    double _MaxSpeed = 0.5;
    double _MaxTurnSpeed = 0.4;
    double _WheelDiameter = 0;
    double _GearRatio = 0;
    
    // Target Values
    double _DistanceInMeters = 0;
    double _DistanceInCM = 0;
    double _DistanceInRotations = 1; // For first time use, the start point might conflict

    // PID
    double _goal = 0;
    double _previousError = 0;
    double _sum = 0;
    double _kP = 0;
    double _kI = 0;
    double _kD = 0;

    int CaseNumber = 1;
    bool WayPointComplete = false;
    bool WayPointStart = true;
};#include "wayfinder_OLD.h"

// using namespace std;
// using namespace wml;

// // Initilize way finder
// WayFinder::WayFinder(double kp, double ki, double kd, wml::Drivetrain &drivetrain, double gearboxReduction, double WheelDiameter) : _drivetrain(drivetrain) {
//   _kP = kp;
//   _kI = ki;
//   _kD = kd;

//   _GearRatio = gearboxReduction;
//   _WheelDiameter = WheelDiameter;
// }

// // Calculate rotations to the waypoint target
// double WayFinder::RotationsToTarget(double p1x, double p1y, double p2x, double p2y) {
//   _DistanceInMeters = sqrt(pow(p2x - p1x, 2) + pow(p2y - p1y, 2) * 1.0);
//   _DistanceInCM = _DistanceInMeters*100;

//   double DistanceInRotations = _GearRatio * (_DistanceInCM/(M_PI * _WheelDiameter));
//   return DistanceInRotations;
// }

// // Config for speed
// void WayFinder::Config(double MaxSpeed, double MaxTurnSpeed) {
//   _MaxSpeed = MaxSpeed;
//   _MaxTurnSpeed = MaxTurnSpeed;
// }

// // Way finders internal PID
// double WayFinder::InternalPID(double dt, double goal, double input) {
//   double error = goal - input;
//   double derror = (error - _previousError)/dt;

//   _sum = _sum + error * dt;

//   double output = _kP * error + _kI * _sum + _kD * derror;
//   output = output > _MaxSpeed ? _MaxSpeed : output;
//   return output;
// }

// // Inverse Numbers
// double WayFinder::InverseNumber(double input) {
//   input = input < 0 ? abs(input) : -input;
//   return input;
// }


// // Using the provided PID and gyro, turn to the target
// void WayFinder::TurnToTarget(double dt, double input, double goal, bool reverse) {
//   double turnSpeed = goal < 0 ? -(InternalPID(abs(dt), abs(goal), abs(input))) : goal > 0 ? (InternalPID(abs(dt), abs(goal), abs(input))) : 0;
//   if (goal > 0) {
//     turnSpeed *= _MaxTurnSpeed;
//   } else if (goal < 0) {
//     turnSpeed = -(abs(turnSpeed) * _MaxTurnSpeed);
//   }

//   _drivetrain.Set(turnSpeed, -turnSpeed);
// }

// // Get Average distance
// double WayFinder::GetDistanceInRotations() {
//   return _DistanceInRotations;
// }

// // Get Average Location
// double WayFinder::GetDrivetrainCurrentLocation() {
//   double CombinedLocation = (fabs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()) + fabs(_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations()));
//   return CombinedLocation/2;
// }


// // Drive to the target waypoint
// void WayFinder::DriveToTarget(double dt, double goal , bool reverse) {
//   // Add power using PID
//   double LeftSpeed = InternalPID(dt, goal, abs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()));
//   double RightSpeed = InternalPID(dt, goal, abs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()));


//   if (reverse) {
//     // Drive straight using gyro
//     LeftSpeed += (_drivetrain.GetConfig().gyro->GetAngle() * (_kP));
//     RightSpeed -= (_drivetrain.GetConfig().gyro->GetAngle() * (_kP));

//     // Inverse Power
//     LeftSpeed = InverseNumber(LeftSpeed);
//     RightSpeed = InverseNumber(RightSpeed);
//   } else {
//     // Drive straight using gyro
//     LeftSpeed -= (_drivetrain.GetConfig().gyro->GetAngle() * (_kP));
//     RightSpeed += (_drivetrain.GetConfig().gyro->GetAngle() * (_kP));
//   }

//   // Limit Power to max speed
//   LeftSpeed *= _MaxSpeed;
//   RightSpeed *= _MaxSpeed;

//   // Set Speed
//   _drivetrain.Set(LeftSpeed, RightSpeed);
// }

// void WayFinder::TestPID(double dt, double goal) {
//   // Add power using PID
//   double LeftSpeed = InternalPID(dt, goal, _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations());
//   double RightSpeed = InternalPID(dt, goal, _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations());

//   // Drive straight using gyro
//   LeftSpeed -= (_drivetrain.GetConfig().gyro->GetAngle() * _kP);
//   RightSpeed += (_drivetrain.GetConfig().gyro->GetAngle() * _kP);

//   // Limit Power to max speed
//   LeftSpeed *= _MaxSpeed;
//   RightSpeed *= _MaxSpeed;

//   // Set Speed
//   _drivetrain.Set(LeftSpeed, RightSpeed);
// }

// bool WayFinder::GetWaypointComplete() {
//   if (WayPointComplete) {
//     WayPointComplete = false;
//     return true;
//   } else {
//     return false;
//   }
// }

// void WayFinder::StartWaypoint() {
//   _drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
//   _drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
//   _drivetrain.GetConfig().gyro->Reset();
//   WayPointStart = false;
// }

// // Ends the turn, Zero's encoders and angles
// void WayFinder::EndTurn() {
//   WayFinder::EndCheckPoint();
//   _drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
//   _drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
// }

// void WayFinder::EndCase() {
//   CaseNumber = 1;
//   WayPointComplete = true;
//   WayPointStart = true;
//   _drivetrain.GetConfig().gyro->Reset();
//   _drivetrain.Set(0, 0);
// }

// void WayFinder::EndCheckPoint() {
//   CaseNumber++;
//   _drivetrain.GetConfig().gyro->Reset();
//   _drivetrain.Set(0, 0);
//   WayPointStart = true;
//   WayPointComplete = false;
// }

// void WayFinder::GotoWaypoint(double wypt1x, double wypt1y, double startAngle, double wypt2x, double wypt2y, double endAngle, bool reverse, double dt) {

//   // Zero if start of new Waypoint/Checkpoint
//   if (WayPointStart) {
//     WayFinder::StartWaypoint();
//   }

//   // Get the distance to the target in rotations
//   _DistanceInRotations = RotationsToTarget(wypt1x, wypt1y, wypt2x, wypt2y);
//   switch (CaseNumber) {
//     case 1:
//       if (startAngle > 0 || startAngle < 0) {
//         if(startAngle < 0) {
//           if (_drivetrain.GetConfig().gyro->GetAngle() > startAngle) {
//             WayFinder::TurnToTarget(dt, _drivetrain.GetConfig().gyro->GetAngle(), startAngle, reverse);
//           } else {
//             WayFinder::EndTurn();
//           }
//         } else if (startAngle > 0) {
//           if (_drivetrain.GetConfig().gyro->GetAngle() < startAngle) {
//             WayFinder::TurnToTarget(dt, _drivetrain.GetConfig().gyro->GetAngle(), startAngle, reverse);
//           } else {
//             WayFinder::EndTurn();
//             break;
//           }
//         } else {
//           WayFinder::EndTurn();
//           break;
//         }
//       } else {
//         WayFinder::EndTurn();
//         break;
//       }
//     break;

//     case 2:
//       // Drive to target
//       if (abs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()) >= _DistanceInRotations || abs(_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations()) >= _DistanceInRotations) {
//         WayFinder::EndCheckPoint();
//         break;
//       } else {
//         WayFinder::DriveToTarget(dt, _DistanceInRotations, reverse);
//       }
//     break;

//     case 3:
//       // Turn to End Angle
//       if (endAngle > 0 || endAngle < 0) {
//         if(endAngle < 0) {
//           if (_drivetrain.GetConfig().gyro->GetAngle() > endAngle) {
//             WayFinder::TurnToTarget(dt, _drivetrain.GetConfig().gyro->GetAngle(), endAngle, reverse);
//           } else {
//             WayFinder::EndCase();
//           }
//         } else if (endAngle > 0) {
//           if (_drivetrain.GetConfig().gyro->GetAngle() < endAngle) {
//             WayFinder::TurnToTarget(dt, _drivetrain.GetConfig().gyro->GetAngle(), endAngle, reverse);
//           } else {
//             WayFinder::EndCase();
//           }
//         } els {
//           WayFie {
//           WayFinder::EndCase();
//         }
//       } else {
//         WayFinder::EndCase();
//       }
//     break;
//   }
// }