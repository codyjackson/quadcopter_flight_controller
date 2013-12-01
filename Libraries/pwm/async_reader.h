#ifndef __ASYNC_READER_H__
#define __ASYNC_READER_H__

#include "time.h"

namespace Pwm
{
	/*
		This class makes two important assumptions which could cause problems.
			1. Frame width doesn't matter. I assume that we will get a steady
			   stream of information from the receiver and those values will
			   always be greater than 0.
			2. The first reading doesn't matter. It's possible that if we turn
			   this on during a HIGH pwm reading the first reading will be
			   innacurate because I don't wait for the signal to toggle from
			   low to high.
	*/
	class InputPin
	{
	public:
		InputPin(unsigned char pinNumber);

		unsigned long get_current_width() const;
		void tick();

	private:
		const unsigned char _pinNumber;
		Time::Microseconds _pinToggledHighTimestamp;
		Time::Microseconds _currentWidth;
	};
}

#endif