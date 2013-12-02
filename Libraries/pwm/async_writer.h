#ifndef __PARALLEL_WRITER_H__
#define __PARALLEL_WRITER_H__

#include "./../time/time.h"

namespace Pwm
{
	class OutputPin
	{
	public:
		OutputPin(unsigned char pinNumber, const Time::Microseconds& frameWidth);

		void set_pulse_width(Time::Microseconds pulseWidth);
		void tick();

	private:
		unsigned char _pinNumber;
		bool _currentState;
		Time::Microseconds _frameWidth;
		Time::Microseconds _pulseWidth;
		Time::Microseconds _nextToggle;
	};
}

#endif