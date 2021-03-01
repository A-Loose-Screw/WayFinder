#include "pidTuner.h"

namespace wayfinder {
	PIDTuner::PIDTuner(RobotControl::Config &config, int xboxPort) : _config(config) {
		_xboxPort = xboxPort;
		_xbox = new wml::controllers::XboxController(_xboxPort);
		// _contGroup = new wml::controllers::SmartControllerGroup(*_xbox);
	}

	void PIDTuner::update() {
		double incrementor = 0.00001;

		if (_xbox->GetButton(wml::controllers::XboxController::kBumperRight)) {
			incrementor = 0.001;
		}

		if (_xbox->GetButton(wml::controllers::XboxController::kBumperLeft)) {
			
			// P
			if (_xbox->GetButton(wml::controllers::XboxController::kB)) {
				*_config.kp_drive += incrementor;
			}

			if (_xbox->GetButton(wml::controllers::XboxController::kA)) {
				*_config.kp_drive -= incrementor;
			}

			// D
			if (_xbox->GetButton(wml::controllers::XboxController::kX)) {
				*_config.kd_drive += incrementor;
			}

			if (_xbox->GetButton(wml::controllers::XboxController::kY)) {
				*_config.kd_drive -= incrementor;
			}
			
			// I
			if (_xbox->GetButton(wml::controllers::XboxController::kStart)) {
				*_config.ki_drive += incrementor;
			}

			if (_xbox->GetButton(wml::controllers::XboxController::kBack)) {
				*_config.ki_drive -= incrementor;
			}
		} else {

			// P
			if (_xbox->GetButton(wml::controllers::XboxController::kB)) {
				*_config.kp_turn += incrementor;
			}

			if (_xbox->GetButton(wml::controllers::XboxController::kA)) {
				*_config.kp_turn -= incrementor;
			}

			// D
			if (_xbox->GetButton(wml::controllers::XboxController::kX)) {
				*_config.kd_turn += incrementor;
			}

			if (_xbox->GetButton(wml::controllers::XboxController::kY)) {
				*_config.kd_turn -= incrementor;
			}
			
			// I
			if (_xbox->GetButton(wml::controllers::XboxController::kStart)) {
				*_config.ki_turn += incrementor;
			}

			if (_xbox->GetButton(wml::controllers::XboxController::kBack)) {
				*_config.ki_turn -= incrementor;
			}
		}

		std::cout << "PID Drive: " << _config.kp_drive << ", " << _config.ki_drive << ", " << _config.kd_drive << std::endl;
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Drive_P").SetDouble(*_config.kp_drive);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Drive_I").SetDouble(*_config.ki_drive);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Drive_D").SetDouble(*_config.kd_drive);

		std::cout << "PID Turn: " << _config.kp_turn << ", " << _config.ki_turn << ", " << _config.kd_turn << std::endl;
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Turn_P").SetDouble(*_config.kp_turn);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Turn_I").SetDouble(*_config.ki_turn);
		nt::NetworkTableInstance::GetDefault().GetTable("WayFinder")->GetSubTable("Config")->GetEntry("Turn_D").SetDouble(*_config.kd_turn);
	}
}