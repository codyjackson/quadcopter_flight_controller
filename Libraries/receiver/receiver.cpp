#include "receiver.h"

#include<Arduino.h>

Receiver::Receiver()
	:_thrustPin(6), _rollPin(4), _pitchPin(5), _thrust(0), _roll(0), _pitch(0)
{}

void Receiver::update()
{
	_thrust = constrain(static_cast<float>(_thrustPin.get_pulse_width().raw()-1150)/800.0f, 0.0f, 0.8f);
	_roll = constrain(static_cast<float>(_rollPin.get_pulse_width().raw()-1500)/400.0f, -1.0f, 1.0f);
	_pitch = constrain(static_cast<float>(_pitchPin.get_pulse_width().raw()-1500)/375.0f, -1.0f, 1.0f);
}

float Receiver::get_thrust_percentage() const
{
	return _thrust;
}

float Receiver::get_roll_percentage() const
{
	return _roll;
}

float Receiver::get_pitch_percentage() const
{
	return _pitch;
}
