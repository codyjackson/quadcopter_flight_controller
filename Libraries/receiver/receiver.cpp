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
	:_rightJoyVerticalPin(10), 
	_rightJoyHorizontalPin(9), 
	_leftJoyVerticalPin(12), 
	_rightJoyVertical(0), 
	_leftTogglePin(11), 
	_rightJoyHorizontal(0), 
	_leftJoyVertical(0), _leftToggle(false), _channel(RIGHT_JOY_VERTICAL)
{}

void Receiver::update()
{
	if(_channel == RIGHT_JOY_VERTICAL)
		update_right_joy_vertical();
	else if(_channel == RIGHT_JOY_HORIZONTAL)
		update_right_joy_horizontal();
	else if(_channel == LEFT_JOY_VERTICAL)
		update_left_joy_vertical();
	else if(_channel == LEFT_TOGGLE)
		update_left_toggle();

	_channel = static_cast<Channel>((_channel+1)%COUNT);
}

float Receiver::get_left_joy_vertical_percentage() const
{
	return _leftJoyVertical;
}

float Receiver::get_right_joy_vertical_percentage() const
{
	return _rightJoyVertical;
}

float Receiver::get_right_joy_horizontal_percentage() const
{
	return _rightJoyHorizontal;
}

bool Receiver::is_in_configuration_mode() const
{
	return _leftToggle;
}

Receiver::PiTarget Receiver::get_pi_target() const
{
	if(_rightJoyVertical > 0.4f)
		return PROPORTIONAL;
	if(_rightJoyHorizontal > 0.4f)
		return INTEGRAL;
	return NONE;
}

float Receiver::get_pi_constant() const
{
	return get_left_joy_vertical_percentage()*5.0f;
}

void Receiver::update_right_joy_vertical()
{
	if(const long value = _rightJoyVerticalPin.get_pulse_width().raw())
	{
		const float range = 375.0f;
		const long centerValue = 1485;
		const float candidateValue = constrain(static_cast<float>(value-centerValue)/range, -1.0f, 1.0f);
		_rightJoyVertical = cancel_noise(_rightJoyVertical, candidateValue);
	}
}


void Receiver::update_right_joy_horizontal()
{
	if(const long value = _rightJoyHorizontalPin.get_pulse_width().raw())
	{
		const float range = 400.0f;
		const long centerValue = 1500;
		const float candidateValue = constrain(static_cast<float>(value-centerValue)/range, -1.0f, 1.0f);
		_rightJoyHorizontal = cancel_noise(_rightJoyHorizontal, candidateValue);
	}
}

void Receiver::update_left_joy_vertical()
{
	if(const long value = _leftJoyVerticalPin.get_pulse_width().raw())
	{
		const float range = 800.0f;
		const long trim = 1160;
		const float candidateValue = constrain(static_cast<float>(value-trim)/range, 0.0f, 0.8f);
		_leftJoyVertical = cancel_noise(_leftJoyVertical, candidateValue);
	}
}


void Receiver::update_left_toggle()
{
	if(const long value = _leftTogglePin.get_pulse_width().raw())
		_leftToggle = value < 1000;
}
