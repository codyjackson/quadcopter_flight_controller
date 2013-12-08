#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "./../pwm/async_writer.h"

class Motor
{
public:
	Motor(const OutputPin& outputPin, unsigned long trim);
	void adjust_output(float percentage);
	void send_signal();

private:
	OutputPin _outputPin;
	unsigned long _trim;
	unsigned long _pulseWidth;
};

#endif