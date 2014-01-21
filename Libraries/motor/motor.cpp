#include "motor.h"

#include <Arduino.h>

Motor::Motor(const OutputPin& outputPin, unsigned long trim)
	:_outputPin(outputPin), _trim(trim), _pulseWidth(0)
{}

void Motor::adjust_output(float percentage)
{
	percentage = percentage < 0.02f ? 0.0f : percentage;
	_pulseWidth = constrain(static_cast<unsigned long>(percentage*1000.0f), 0, 1000) + _trim + 1000;
}

void Motor::send_signal()
{
	_outputPin.turn_on();

	//I'm adding this condition because if the ESC doesn't receive an initial 1000 _pulseWidth for lowest
	//throttle it won't start.
	if(1000+_trim == _pulseWidth)
		delayMicroseconds(1000);
	else
		delayMicroseconds(_pulseWidth);
	_outputPin.turn_off();
}