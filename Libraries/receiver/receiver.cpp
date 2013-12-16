#include "receiver.h"

#include<Arduino.h>

namespace
{
	float cancel_noise(float oldValue, float newValue)
	{
		return abs(oldValue-newValue) > 0.01 ? newValue : oldValue;
	}
}

Receiver::Receiver()
	:_thrustPin(6), _rollPin(4), _pitchPin(5), _thrust(0), _roll(0), _pitch(0), _channel(THRUST)
{}

void Receiver::update()
{
	switch(_channel)
	{
		case THRUST:
			_thrust = cancel_noise(_thrust, constrain(static_cast<float>(_thrustPin.get_pulse_width().raw()-1160)/800.0f, 0.0f, 0.8f));
		break;
		case ROLL:
			_roll = cancel_noise(_roll, constrain(static_cast<float>(_rollPin.get_pulse_width().raw()-1500)/400.0f, -1.0f, 1.0f));
		break;
		case PITCH:
			_pitch = cancel_noise(_pitch, constrain(static_cast<float>(_pitchPin.get_pulse_width().raw()-1500)/375.0f, -1.0f, 1.0f));
		break;
	};
	_channel = static_cast<Channel>((_channel+1)%COUNT);
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
