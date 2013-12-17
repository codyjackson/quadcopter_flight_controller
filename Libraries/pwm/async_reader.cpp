#include <Arduino.h>
#include "async_reader.h"


InputPin::InputPin(unsigned char pinNumber)
	:_pinNumber(pinNumber)
{
	pinMode(_pinNumber, INPUT);
}

bool InputPin::get_signal() const
{
	return digitalRead(_pinNumber);
}

Time::Microseconds InputPin::get_pulse_width() const
{
	return Time::Microseconds(pulseIn(_pinNumber, HIGH));
}
