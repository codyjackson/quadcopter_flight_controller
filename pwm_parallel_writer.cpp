#include "pwm_parallel_writer.h"
#include <Arduino.h>

namespace Pwm
{

	OutputPin::OutputPin(unsigned char pinNumber, const Time::Microseconds& frameWidth)
		:_pinNumber(pinNumber), _currentState(false), _frameWidth(frameWidth)
	{}
	void OutputPin::initialize()
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
			_nextToggle = _currentState ? currentTime + (_frameWidth - _pulseWidth) : currentTime + _pulseWidth;
			_currentState = !_currentState;
			digitalWrite(_pinNumber, _currentState);
		}
	}
}
