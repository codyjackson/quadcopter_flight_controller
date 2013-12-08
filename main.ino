#include <Arduino.h>
#include <Wire.h>

#include "time.h"
#include "async_reader.h"
#include "async_writer.h"
#include "receiver.h"
#include "accelerometer.h"
#include "gyroscope.h"
#include "i2c.h"
#include "imu.h"
#include "vec.h"

class ScopedTimer
{
public:
	ScopedTimer()
		:m_start(micros())
	{}

	~ScopedTimer()
	{
		Serial.println(micros()-m_start);
	}

private:
	ScopedTimer(const ScopedTimer&);
	const ScopedTimer& operator =(const ScopedTimer&);

	unsigned long m_start;
};

Receiver r;
Imu imu;
void setup()
{
	Serial.begin(9600);
	imu.initialize();
}

void loop()
{
	{
		ScopedTimer t;
		r.update();
	}

	imu.update();
}

