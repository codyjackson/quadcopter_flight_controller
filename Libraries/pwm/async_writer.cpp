#include "async_writer.h"
#include <Arduino.h>


OutputPin::OutputPin(unsigned char pinNumber)
	:_pinNumber(pinNumber)
{
	pinMode(_pinNumber, OUTPUT);
	digitalWrite(_pinNumber, LOW);
}

void OutputPin::turn_on()
{
	digitalWrite(_pinNumber, HIGH);
}

void OutputPin::turn_off()
{
	digitalWrite(_pinNumber, LOW);
}
