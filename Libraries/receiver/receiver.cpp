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
	if(_channel == THRUST)
		update_thrust();
	else if(_channel == ROLL)
		update_roll();
	else
		update_pitch();

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

void Receiver::update_thrust()
{
	if(const long value = _thrustPin.get_pulse_width().raw())
	{
		const float thrustRadioRange = 800.0f;
		const long thrustRadioTrim = 1160;
		const float candidateThrustValue = constrain(static_cast<float>(value-thrustRadioTrim)/thrustRadioRange, 0.0f, 0.8f);
		_thrust = cancel_noise(_thrust, candidateThrustValue);
	}
}

void Receiver::update_roll()
{
	if(const long value = _rollPin.get_pulse_width().raw())
	{
		const float rollRadioRange = 400.0f;
		const long rollRadioCenter = 1500;
		const float candidateRollValue = constrain(static_cast<float>(value-rollRadioCenter)/rollRadioRange, -1.0f, 1.0f);
		_roll = cancel_noise(_roll, candidateRollValue);
	}
}

void Receiver::update_pitch()
{
	if(const long value = _pitchPin.get_pulse_width().raw())
	{
		const float pitchRadioRange = 375.0f;
		const long pitchRadioCenter = 1485;
		const float candidatePitchValue = constrain(static_cast<float>(value-pitchRadioCenter)/pitchRadioRange, -1.0f, 1.0f);
		_pitch = cancel_noise(_pitch, candidatePitchValue);
	}
}
