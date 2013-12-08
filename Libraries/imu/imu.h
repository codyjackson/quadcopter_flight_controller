#ifndef __IMU_H__
#define __IMU_H__

#include "accelerometer.h"
#include "gyroscope.h"

class Imu
{
public:
	Imu();
	void initialize();

	void update();

	float get_roll() const;
	float get_pitch() const;

private:
	Vec3 get_orientation();

	unsigned long _timestamp;
	Vec3 _orientationAccumulator;

	Accelerometer _accelerometer;
	Gyroscope _gyroscope;
};

#endif