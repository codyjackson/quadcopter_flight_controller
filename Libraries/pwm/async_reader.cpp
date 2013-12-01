#include <Arduino.h>
#include "async_reader.h"

namespace Pwm
{
	InputPin::InputPin(unsigned char pinNumber)
		:_pinNumber(pinNumber), _pinToggledHighTimestamp(0), _currentWidth(0)
	{
		pinMode(_pinNumber, INPUT);
	}

	unsigned long InputPin::get_current_width() const
	{
		return _currentWidth.raw();
	}

	void InputPin::tick()
	{
		bool pinValue = digitalRead(_pinNumber);
		bool isReading = _pinToggledHighTimestamp != Time::Microseconds(0);
		if(!isReading && pinValue)
			_pinToggledHighTimestamp = Time::Microseconds::since_start();
		else if(isReading && !pinValue)
		{
			_currentWidth = Time::Microseconds::since_start() - _pinToggledHighTimestamp;
			_pinToggledHighTimestamp = Time::Microseconds(0);
		}
	}
}