#include "pwm_parallel_writer.h"
#include <Arduino.h>

namespace Pwm
{
	OutputPin::OutputPin(unsigned char pinNumber, unsigned short width)
		:_pinNumber(pinNumber), _width(width)
	{}

	void OutputPin::initialize()
	{
		pinMode(_pinNumber, OUTPUT);
	}

	void OutputPin::set_width(unsigned short width)
	{
		_width = width;
	}

	unsigned char OutputPin::get_pin_number() const
	{
		return _pinNumber;
	}

	unsigned short OutputPin::get_width() const
	{
		return _width;
	}


	ParallelWriter::PinWriter::PinWriter()
	{}

	ParallelWriter::PinWriter::PinWriter(const OutputPin& pin)
		:_pinNumber(pin.get_pin_number()), _width(pin.get_width()), _startTime(0), _targetEndTime(0)
	{
		digitalWrite(_pinNumber, LOW);
	}

	bool ParallelWriter::PinWriter::send_pulse()
	{
		if(_startTime && (micros() >= _targetEndTime))
		{
			digitalWrite(_pinNumber, LOW);
			return true;
		}

		if(!_startTime)
		{
			_startTime = micros();
			_targetEndTime = _startTime + 1000 + _width;
			digitalWrite(_pinNumber, HIGH);
		}
		return false;
	}
}