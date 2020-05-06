#pragma once
#include "Path.h"

#ifdef USING_WML
 #include "Drivetrain.h"
#endif

namespace WayFinder {
  /**
   * Main class for wayfinder, include into your code and setup for use
   */
  class WayFinder : public Path {
   public:
   #ifdef USING_WML
    WayFinder(wml::Drivetrain &drivetrain, double gearboxReduction, double wheelDiameter) : _drivetrain(drivetrain) {
      _gearboxReduction = gearboxReduction;
      _wheelDiameter = wheelDiameter;
    }
   #else
    WayFinder(double gearboxReduction, double wheelDiameter) {
      _gearboxReduction = gearboxReduction;
      _wheelDiameter = wheelDiameter;
    }
   #endif
    ~WayFinder() {
      printf("Wayfinder Object Deconstructed");
    }

    /** 
     * config your auto, schedule new PID gains or change reduction or speed values mid auto
     */
    void autoConfig(double kp, double ki, double kd, double gearboxReduction, double wheelDiameter, double maxSpeed, double maxTurnSpeed);

    /** 
     * Set the spline influencers to get a more subtle or extreme curve between waypoints (will effect whole path)
     */
    void setSplineInfluencers(double q1 = 0, double q2 = 0, double q3 = 0, double q4 = 0);

    /**
     * follow path automatically (WML only)
     */
    void followPath(Path::lPath path, bool reversed);

    /**
     * follow path automatically (WML only)
     */
    void followPath(Path::sPath path, bool reversed);

    /**
     * follow a group of paths automatically (WML only)
     */
    void followPathGroup(std::vector<Path::lPath> paths, bool reversed);
    
    /**
     * follow group of paths automatically (WML only)
     */
    void followPathGroup(std::vector<Path::sPath> paths, bool reversed);

    /**
     * Get Values for drivetrain if your not using wml,
     * or have a different system for setting power to drivetrain
     * Returns pair of doubles for drivetrain motors
     */
    std::pair<double, double> getDrivetrainPower();

    /**
     * Get values for robot angle if your not using wml,
     * or have a different system for getting angle
     * Returns double for angle in degrees (Set radians true for radians)
     */
    double getDrivetrainAngle(bool radians = false);


   private:

    // PID Values
    double *_kp;
    double *_kd;
    double *_ki;

    #ifdef USING_WML
      wml::Drivetrain &_drivetrain;
    #endif
    double _gearboxReduction;
    double _wheelDiameter;

    double _maxSpeed;
    double _maxTurnSpeed;
  };
}