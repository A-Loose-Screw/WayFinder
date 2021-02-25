#include "controllers/Controllers.h"
#include "robotControl.h"

namespace wayfinder {
	class PIDTuner {
	 public:

		/**
		 * Initialize PID Tuner
		 */
		PIDTuner(RobotControl::Config &config, int xboxPort = 3);

		/**
		 * Main updater for tuner
		 * Controls:
		 * 
		 */
		void update();
	 private:
		RobotControl::Config &_config;
		int _xboxPort;
		wml::controllers::XboxController *_xbox;
		// wml::controllers::SmartControllerGroup *_contGroup;
		bool turnPID = false;
	};
}