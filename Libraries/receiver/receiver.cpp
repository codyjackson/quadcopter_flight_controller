#include "receiver.h"
#include "./../pwm/async_reader.h"


Receiver::Receiver()
	:_thrust(0), _roll(0), _pitch(0)
{}

void Receiver::update()
{
	InputPin thrustPin(5);
	InputPin rollPin(2);
	InputPin pitchPin(1);

	_thrust = static_cast<float>(thrustPin.get_pulse_width().raw()-1100)/800.0f;
	_roll = static_cast<float>(rollPin.get_pulse_width().raw()-1500)/800.0f;
	_pitch = static_cast<float>(pitchPin.get_pulse_width().raw()-1500)/800.0f;
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
