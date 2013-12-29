#include "copter.h"


Copter::Copter()
:	_thrust(0),

	_rollPi(0, 0),
	_pitchPi(0, 0),

	_frontLeftMotor(OutputPin(5), 0), 
	_frontRightMotor(OutputPin(6), 0), 
	_backRightMotor(OutputPin(7), 0), 
	_backLeftMotor(OutputPin(8), 0)
{}

void Copter::initialize()
{
	_imu.initialize();
}

void Copter::update()
{
	_imu.update();
	const float rollOut = _stabalizing ? _rollPi.calculate(_imu.get_roll())/360.0f : 0.0f;
	const float pitchOut = _stabalizing ? _pitchPi.calculate(_imu.get_pitch())/360.0f : 0.0f;

	_frontLeftMotor.adjust_output(_thrust + pitchOut + rollOut);
	_frontRightMotor.adjust_output(_thrust + pitchOut - rollOut);

	_backLeftMotor.adjust_output(_thrust - pitchOut + rollOut);
	_backRightMotor.adjust_output(_thrust - pitchOut - rollOut);

	_frontLeftMotor.send_signal();
	_frontRightMotor.send_signal();
	_backRightMotor.send_signal();
	_backLeftMotor.send_signal();
}

void Copter::set_thrust_percentage(float thrust)
{
	_thrust = thrust;
}

void Copter::set_target_roll(float roll)
{
	_rollPi.set_target(roll);
}

void Copter::set_target_pitch(float pitch)
{
	_pitchPi.set_target(pitch);
}

void Copter::update_pi_constants(float p, float i)
{
	_rollPi = PiController(p, i);
	_pitchPi = PiController(p, i);
}

void Copter::turn_on_stabalization()
{
	if(_stabalizing)
		return;

	_pitchPi.reset();
	_stabalizing = true;
}
	
void Copter::turn_off_stabalization()
{
	_stabalizing = false;
}