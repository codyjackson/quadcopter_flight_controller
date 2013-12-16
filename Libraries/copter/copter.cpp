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
	const float rollOut = _rollPid.calculate(_imu.get_roll());
	const float pitchOut = _pitchPid.calculate(_imu.get_pitch());

	_frontLeftMotor.set_thrust_percentage(_thrust - _pitchPid - rollPid);
	_frontRightMotor.set_thrust_percentage(_thrust - _pitchPid + rollPid);

	_backLeftMotor.set_thrust_percentage(_thrust + _pitchPid - rollPid);
	_backRightMotor.set_thrust_percentage(_thrust + _pitchPid + rollPid);

}

void Copter::set_thrust_percentage(float thrust)
{
	_thrust = thrust;
}

void Copter::set_target_roll(float roll)
{
	_rollPid.set_target(roll);
}

void Copter::set_target_pitch(float pitch)
{
	_pitchPid.set_target(pitch);
}