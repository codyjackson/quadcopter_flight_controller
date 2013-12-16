#include "pi_controller.h"

PiController::PiController(float kp, float ki)
:_kp(kp), _ki(ki), _accumulatedError(0), _target(0), _lastCalculation(0)
{}

void PiController::set_target(float target)
{
	_target = target;
}

float PiController::calculate(float actual)
{
	Time::Microseconds stamp = Time::Microseconds::since_start();
	if(_lastCalculation == Time::Microseconds(0))
	{
		_lastCalculation = stamp;
		return 0;
	}

	float dError = _target - actual;
	float dt = static_cast<float>(stamp - _lastCalculation)/1000000.0f;
	_accumulatedError += dError * dt;

	_lastCalculation = stamp;
	return _kp*dError + _ki*_accumulatedError;
}

void PiController::reset()
{
	_lastCalculation = Time::Microseconds(0);
	_accumulatedError = 0.0f;
}