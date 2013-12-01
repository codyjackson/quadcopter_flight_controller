#include "async_writer.h"
#include <Arduino.h>

namespace Pwm
{

	OutputPin::OutputPin(unsigned char pinNumber, const Time::Microseconds& frameWidth)
		:_pinNumber(pinNumber), _currentState(false), _frameWidth(frameWidth)
	{
		pinMode(_pinNumber, OUTPUT);
		digitalWrite(_pinNumber, _currentState);
	}

	void OutputPin::set_pulse_width(Time::Microseconds pulseWidth)
	{
		_pulseWidth = pulseWidth;
	}

	void OutputPin::tick()
	{
		Time::Microseconds currentTime(Time::Microseconds::since_start());
		if( currentTime >= _nextToggle)
		{
			_currentState = !_currentState;
			digitalWrite(_pinNumber, _currentState);
			_nextToggle = _currentState ? currentTime + _pulseWidth : currentTime + (_frameWidth - _pulseWidth);
		}
	}
}
