#ifndef __INPUT_PIN_H__
#define __INPUT_PIN_H__

#include "./../time/time.h"

class InputPin
{
public:
	InputPin(unsigned char pinNumber);

	bool get_signal() const;
	Time::Microseconds get_pulse_width() const;

private:
	const unsigned char _pinNumber;
};

#endif