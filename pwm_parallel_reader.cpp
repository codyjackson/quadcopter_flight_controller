#include "pwm_parallel_reader.h"
#include <Arduino.h>

namespace Pwm
{
	InputPin::InputPin(char pinNumber)
		:_pinNumber(pinNumber), _currentWidth(0)
	{}

	void InputPin::initialize()
	{
		pinMode(_pinNumber, INPUT);
	}

	short InputPin::get_current_width() const
	{
		return _currentWidth;
	}

	char InputPin::get_pin_number() const
	{
		return _pinNumber;
	}

	void InputPin::update_width(short width)
	{
		_currentWidth = width;
	}

	ParallelReader::PinReader::PinReader()
	{}

	ParallelReader::PinReader::PinReader(const InputPin& pin)
		:_pinNumber(pin.get_pin_number()), _previousPinValue(digitalRead(_pinNumber)), _currentPinValue(_previousPinValue), _startTime(0), _endTime(0)
	{}

	short ParallelReader::PinReader::get_updated_width() const
	{
		return _endTime - _startTime;
	}

	bool ParallelReader::PinReader::look_for_width_update_tick()
	{
		if(_startTime && _endTime)
			return true;

		_currentPinValue = digitalRead(_pinNumber);
		if(_currentPinValue && !_previousPinValue)
			_startTime = micros();

		if(!_currentPinValue && _previousPinValue && _startTime)
			_endTime = micros();

		_previousPinValue = _currentPinValue;
		return false;
	}
}