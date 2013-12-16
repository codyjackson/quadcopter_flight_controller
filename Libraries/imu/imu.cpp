#include "imu.h"

Imu::Imu()
	:_timestamp(0)
{
}

void Imu::initialize()
{
	_accelerometer.initialize();
	_gyroscope.initialize();
}

void Imu::update()
{
	if(_timestamp == 0)
	{
		_timestamp = millis();
		return;
	}

	const unsigned long newTimeStamp = millis();
	const float dt = (newTimeStamp - _timestamp)/1000.0f;
	_timestamp = newTimeStamp;

	const Vec3 va = _accelerometer.get_angles();
	const Vec3 ga = _gyroscope.get_angles(dt);
	
	_orientationAccumulator += ga;
	_orientationAccumulator *= 0.98;
	_orientationAccumulator += va*0.02;
}

float Imu::get_roll() const
{
	return _orientationAccumulator.x();
}

float Imu::get_pitch() const
{
	return -_orientationAccumulator.y();
}