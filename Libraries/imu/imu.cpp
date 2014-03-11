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
	
	_orientation += ga;
	_orientation *= 0.96;
	_orientation += va*0.04;
}

float Imu::get_roll() const
{
	return _orientation.x();
}

float Imu::get_pitch() const
{
	return -_orientation.y();
}