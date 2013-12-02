#include <Arduino.h>
#include "async_reader.h"

namespace Pwm
{
	InputPin::InputPin(unsigned char pinNumber)
		:_pinNumber(pinNumber), _pinToggledHighTimestamp(0)
	{
		pinMode(_pinNumber, INPUT);
		_oldPinValue = digitalRead(_pinNumber);
	}

	Time::Microseconds InputPin::tick()
	{
		bool pinValue = digitalRead(_pinNumber);
		Time::Microseconds curTime = Time::Microseconds::since_start();
		
		bool oldPinValue = _oldPinValue;
		_oldPinValue = pinValue;

		if(pinValue && !oldPinValue)
			_pinToggledHighTimestamp = curTime;
		else if(!pinValue && oldPinValue && (_pinToggledHighTimestamp != Time::Microseconds(0)))
			return curTime - _pinToggledHighTimestamp;
		return Time::Microseconds(0);
	}
}