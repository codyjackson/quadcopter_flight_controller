#include "copter.h"

Copter::Copter()
{
	//TODO
}

void Copter::update()
{
	const float rollOut = _rollPid.update();
	const float pitchOut = _pitchPid.update();

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