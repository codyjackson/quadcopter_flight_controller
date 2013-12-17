#ifndef __PI_CONTROLLER_H__
#define __PI_CONTROLLER_H__

#include "./../time/time.h"

class PiController
{
public:
	PiController(float kp, float ki);

	void set_target(float target);
	float calculate(float actual);
	void reset();

private:
	const float _kp;
	const float _ki;
	float _accumulatedError;
	float _target;
	Time::Microseconds _lastCalculation;
};

#endif