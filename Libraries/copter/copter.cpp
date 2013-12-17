#include "copter.h"


Copter::Copter()
:	_thrust(0),

	_rollPi(2, 0.25),
	_pitchPi(2, 0.25),

	_frontLeftMotor(OutputPin(8), 160), 
	_frontRightMotor(OutputPin(9), 160), 
	_backRightMotor(OutputPin(10), 10), 
	_backLeftMotor(OutputPin(11), 155)
{}

void Copter::initialize()
{
	_imu.initialize();
}

void Copter::update()
{
	const float rollOut = _rollPi.calculate(_imu.get_roll());
	const float pitchOut = _pitchPi.calculate(_imu.get_pitch());

	_frontLeftMotor.adjust_output(_thrust - pitchOut - rollOut);
	_frontRightMotor.adjust_output(_thrust - pitchOut + rollOut);

	_backLeftMotor.adjust_output(_thrust + pitchOut - rollOut);
	_backRightMotor.adjust_output(_thrust + pitchOut + rollOut);

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