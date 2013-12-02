#ifndef __ASYNC_READER_H__
#define __ASYNC_READER_H__

#include "./../time/time.h"

namespace Pwm
{
	class InputPin
	{
	public:
		InputPin(unsigned char pinNumber);
		/*
			Tick is assumed to be called on a regular interval. If tick is called irregularly than accuracy cannot be certain.
			The accuracy is determined by the time period between calls. If it takes 10us between calls than the accuracy is +- 10us.

			If you can only garuntee the regular interval for enough time to get a single pulse width reading. Next time you come to call tick
			simply construct a new InputPin and all should be well.

			return: Tick return a time greater than 0us whenever a pulse width is fully read. Otherwise 0us is returned.
		*/
		Time::Microseconds tick();

	private:
		unsigned char _pinNumber;
		bool _oldPinValue;
		Time::Microseconds _pinToggledHighTimestamp;
	};
}

#endif